function calibrationGUI( comPort )
% This function creates a GUI that can be used to calibrate a linear sensor.
% This script is part of the code for the SEDS test stand.
%
% Inputs:
% comPort - String - The com port you are reading from (Ex: 'COM3')
%
% Ari Rubinsztejn
% ari@gereshes.com
% www.gereshes.com

x.m=0;
dt=.001;
x.Loads=0;
x.points=[];
path = 'C:\';%Write your path here
%Deletes any existing COM objects
try
    delete(instrfindall);
catch
end

%Opens your serail port
try
    s = serial(comPort);
    set(s,'BaudRate',115200);
    fopen(s);
catch
    error('Change your COM port')    
end

timeout = 10;
maxPoint=0;

%Creates the GUI
set(0,'units','pixels')
Pix_SS = get(0,'screensize');
f=figure('Visible','On','Position',[300,300,500,500]);
 set(f,'CloseRequestFcn','closeMe')
codeLogoImage = axes('Units','pixels','Position',[30,300,100,250]);
axes(codeLogoImage)
title = uicontrol('Style','text','String','Calibration','Position', [0,400,500,50],'FontSize',20,'FontWeight','bold');
axis off
axis image
Write = uicontrol('Style','pushbutton','String','Write','FontSize',14,'Position', [330 200 140 50],'Callback',@write);
Run = uicontrol('Style','pushbutton','String','Start','FontSize',20,'Position', [330 250 140 100],'Callback',@run);
weightEnter  = uicontrol('Style','Edit','Position', [330 350 140 30]);
weightTitle = uicontrol('Style','text','String','Weight (kg)','Position', [330 380 140 30],'FontSize',10);
meanTitle = uicontrol('Style','text','String','Mean =','Position', [10 360 140 40],'FontSize',10);
varTitle = uicontrol('Style','text','String','Var  =','Position', [10 310 140 40],'FontSize',10);
bTitle = uicontrol('Style','text','String','  b  =','Position', [10 260 140 40],'FontSize',10);
mTitle = uicontrol('Style','text','String','  m  =','Position', [10 210 140 40],'FontSize',10);

graphLocal = axes('Units','pixels','Position',[50,40,420,160]);
xlabel('Weight (Kg)')
ylabel('Value')
grid minor

    function run(~,~)
        %A sub function that reads the data at a single weight from the com 
        %port, stores it, and calcualte some statistics aobut it.
        tic
        stability=1;
        time=0;
        rawData=zeros(2,ceil(timeout/dt)+100);
        c=1;
        oldMean=-1;
        flushinput(s)
        while(stability && time<timeout)
            try
                dataString=fgetl(s);
                colonIndex=strfind(dataString,':');
                rawData(:,c)=[str2double(dataString(1:colonIndex(1)-1));str2double(dataString(colonIndex(1)+1:end))];
                if(mod(c,100)==0)
                    %plot(rawData(2,ceil(c/5):c))
                    
                    if(abs(oldMean-mean(rawData(2,1:c)))<.01)
                        stability=0;
                        break;
                    else
                        oldMean=mean(rawData(2,1:c));
                    end
                end
                c=c+1;
            catch
            end

        end
        tempStr.data=rawData(:,find(rawData(1,:)));
        tempStr.mean=mean(tempStr.data(2,:));
        tempStr.std=std(tempStr.data(2,:));
        weightName=regexprep(weightEnter.String,'\.','p');
        tempString=strcat('x.W',weightName,'=tempStr;');
        eval(tempString)
        if (maxPoint<str2double(weightEnter.String))
            maxPoint=str2double(weightEnter.String);
        end
        meanTitle = uicontrol('Style','text','String',strcat('Mean =',num2str(tempStr.mean)),'Position', [10 360 140 40],'FontSize',10);
        varTitle = uicontrol('Style','text','String',strcat('Var  =',num2str(tempStr.std)),'Position', [10 310 140 40],'FontSize',10);
        x.Loads=x.Loads+1;
        x.points=[x.points,[str2double(weightEnter.String);tempStr.mean]];
        if(x.Loads>=2)
            pFit=polyfit(x.points(1,:),x.points(2,:),1);
            x.b= pFit(2);
            x.m= pFit(1);
            bTitle = uicontrol('Style','text','String',strcat('b  =',num2str(x.b)),'Position', [10 260 140 40],'FontSize',10);
            mTitle = uicontrol('Style','text','String',strcat('m  =',num2str(x.m)),'Position', [10 210 140 40],'FontSize',10);
            plot([0, maxPoint],[x.b,(x.m*maxPoint)+x.b]);
            hold on
            scatter(x.points(1,:),x.points(2,:));
            hold off
        end
    end
    function write(~,~)
        %Writes the data to a specific location
        save(path,'x')
        save(strcat(strcat(path,'-',(regexprep(num2str(now),'\.','p')))),'x')
        msgbox('File Saved')
        pause(1.3)
        fclose(s)
        close(f)
    end

end
