% This script takes the holderCell from loadcellArduniReadoutMk2 and the
% calibration data form calibrationGUI and then turns the raw data from the
% test into a thrust curve and calculates key stats like average thrust,
% max thrust, etc. While you will manually have to change the calibration 
% coefficients you can just leave the holderCell in your workspace. This 
% script is part of the code for the SEDS test stand.
%
% Ari Rubinsztejn
% ari@gereshes.com
% www.gereshes.com

tic
disp('Processing ...') 
%%Holder cell to timestamped matrix
holderCellLength=length(holderCell);
pPrime=holderCellLength;
for p=2:holderCellLength-1
    
    if (isempty(holderCell{p})&&isempty(holderCell{p+1}))
        pPrime=p-1;
        break
    end
end
disp('... used cell length identified ...')
holder=NaN(2,pPrime);
loop=0;
disp('... converting cells to array ...')
for p=1:pPrime
    %try
        index=strfind(holderCell{p},':');
        if(length(index)==1)
            if(index(1)>9)
                continue
            end
            holder(1,p)=str2double(holderCell{p}(1:index(1)-1))/(1E3);
            holder(2,p)=str2double(holderCell{p}(index(1)+1:end));
            oldIndex=index(1);
            loop=1;
        end
        if (mod(p,round(pPrime/1000))==0)
            clc
            disp('... converting cells to array ...')
            disp([num2str(round(100*p/pPrime,2)),'% converted'])
        end
    %catch
   % end
end
disp('... reviewing and removing faulty data ...')
for p=length(holder):-1:1
    try

        if(isnan(holder(1,p))||isnan(holder(2,p)))
            holder(:,p)=[];
        end
    catch
    end
    if (mod(p,round(pPrime/1000))==0)
            clc
            disp('... reviewing and removing faulty data ...')
            disp([num2str(round(25*(length(holder)-p)/length(holder),2)),'% reviewed'])
    end
end    

fifthElementTime = median(holder(1,1:10));
timeStep=mean(diff(holder(1,1:100)));
firstElementTime = fifthElementTime - (4*timeStep);
secondElementTime = fifthElementTime - (3*timeStep);
if(abs(holder(1,1)-firstElementTime)>fifthElementTime)
    holder(1,1)=firstElementTime;
end
if(abs(holder(1,2)-secondElementTime)>fifthElementTime)
    holder(1,2)=secondElementTime;
end
for c=3:length(holder)-1
    if (holder(1,c)<holder(1,c-1))
        holder(1,c)=((holder(1,c-1)-holder(1,c-2))/2)+holder(1,c-1);
    elseif(holder(1,c)>holder(1,c+1))
        holder(1,c)=((holder(1,c-1)-holder(1,c-2))/2)+holder(1,c-1);
    end
    if (mod(p,round(pPrime/1000))==0)
            clc
            disp('... reviewing and removing faulty data ...')
            disp([num2str(round(25*p/length(holder),2)+25),'% reviewed'])
    end
end

for c=3:length(holder)
    if (holder(2,c)>(2^31))
        holder(2,c)=((holder(2,c-1)-holder(2,c-2))/2)+holder(2,c-1);
    elseif(holder(2,c) <-1*(2^31))
        holder(2,c)=((holder(2,c-1)-holder(2,c-2))/2)+holder(2,c-1);
    end
    if (mod(p,round(pPrime/1000))==0)
            clc
            disp('... reviewing and removing faulty data ...')
            disp([num2str(round(25*p/length(holder),2)+50),'% reviewed'])
    end
end
startMean = mean(holder(2,1:100));
startStd = std(holder(2,1:100));
for c=3:length(holder)
    if(holder(2,c) <startMean-(2*startStd))
        holder(2,c)=((holder(2,c-1)-holder(2,c-2))/2)+holder(2,c-1);
    end
    if (mod(p,round(pPrime/1000))==0)
            clc
            disp('... reviewing and removing faulty data ...')            
            disp([num2str(round(25*p/length(holder),2)+75),'% reviewed'])
    end
end    
clc
disp('... faulty data removed ...')
%% Initializatioiin
stats= struct();
if(isnan(holder(2,1)))
    holder(:,1)=[];
end
%% Calibration setting
convFact = 35.1986; %This corresponds to m in the calibration script
aLoad =   49.9962;  %This corresponds to b in the calibration script
%% convert to Load
%timestampedLoad = [holder(1,:);(convFact*(holder(2,:)-aReading))+aLoad];
timestampedLoad = [holder(1,:);9.81*(holder(2,:)-aLoad)/convFact];
if(timestampedLoad(2,1)~=0)
    timestampedLoad(2,:)=timestampedLoad(2,:)-timestampedLoad(2,1);
end

disp('... digital counts converted to weight ...')
%% Lop off unused steps
endMeasurement=length(timestampedLoad);
for c=length(timestampedLoad):-1:1
    if(timestampedLoad(1,c)==0)
        continue
    else
        endMeasurement=c;
        break
    end
end
timestampedLoad=timestampedLoad(:,1:endMeasurement);

disp('... unused time steps removed ...')
%% Isolate Burn
burnIsolated=timestampedLoad;
isoCode = 0;%0 for start and end. 1 for start-243  2 for start-243 end+243. 3 for end+243
burnStart = 1;
burnEnd = length(burnIsolated);
threashold=1;
zeroForceMean = mean(burnIsolated(1,1:200));
zeroForceStd = std(burnIsolated(1,1:200));
for(d=1:length(burnIsolated)) %#ok<*NO4LP>
    if(burnIsolated(2,d)<=(zeroForceStd*threashold)+zeroForceMean)
        continue
    else
        if(d>244)
            burnStart=d-243;
            isoCode=1;
        else
            burnStart=d-floor(d*.25);
        end
        break
    end
end

for(c=length(burnIsolated):-1:1)
    if(burnIsolated(2,c)<=(zeroForceStd*threashold)+zeroForceMean)
        continue
    else
        if((length(burnIsolated)-c)>243)
            burnEnd=c+243;
            if (isoCode==1)
                isoCode=2;
            else
                isoCode=3;
            end
        else
            burnEnd=round((length(burnIsolated))-(c*.25));
        end
        break
    end
end
burnIsolated=timestampedLoad(:,burnStart:burnEnd);
if(isoCode==1)
burnIso0=timestampedLoad(:,burnStart+243:burnEnd);
elseif(isoCode==2)
burnIso0=timestampedLoad(:,burnStart+243:burnEnd-243);    
elseif(isoCode==3)
burnIso0=timestampedLoad(:,burnStart:burnEnd-243);
else
    burnIso0=burnIsolated;
end

disp('... burn isolated ...');
%% Impulse
totalImpulse = 0;
impulse=zeros(1,length(burnIsolated)-1);
for c=1:length(burnIsolated)-1
    impulse(c)=(burnIsolated(1,c+1)-burnIsolated(1,c))*(burnIsolated(2,c+1)+burnIsolated(2,c))/2;
    if (round(impulse(c),11)<=0)
        impulse(c)=0;
    end
end

%% Stats
stats.maxForceSingle = max(timestampedLoad(2,:));
[~,maxInd]=max(timestampedLoad(2,:));
stats.maxForceMean = mean(timestampedLoad(2,maxInd-5:maxInd+5));%lbs
stats.maxForceMedian = median(timestampedLoad(2,maxInd-5:maxInd+5));%lbs
stats.avgForce = mean(burnIso0);%lbs
stats.timeStepSize = mean(diff(burnIsolated(1,1:end/2)));%seconds
stats.impulseDiscrete=impulse;%lbs * s
stats.impulseTotal=sum(impulse);%lbs * s
stats.burnTime=burnIso0(1,end)-burnIso0(1,1);
struct2table(stats)
%% Ploting
disp('... drawing plots')
figure
plot(timestampedLoad(1,:),timestampedLoad(2,:))
hold off
title('Load Vs Time')
ylabel('Load (Newtons)')
xlabel('Time (seconds)')
figure
scatter(timestampedLoad(1,:),timestampedLoad(2,:))
title('Load Vs Time (scatter)')
ylabel('Load (Newtons)')
xlabel('Time (seconds)')
figure
plot(burnIsolated(1,:),burnIsolated(2,:))
title('Load Vs Time (Isolated Burn)')
ylabel('Load (Newtons)')
xlabel('Time (seconds)')
figure
scatter(burnIsolated(1,1:end-1),impulse(1,:))
title('Impulse as a Function of time')
ylabel('Impulse (Newtons * s)')
xlabel('Time (seconds)')
disp(['Total time elapsed: ',num2str(toc)])
disp('Done.')