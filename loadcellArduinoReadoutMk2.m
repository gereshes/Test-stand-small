% This script reads in a signal from the computers serial line and stores
% it as a cell in Matlab. This script is part of the code for the SEDS test
% stand.
%
% Ari Rubinsztejn
% ari@gereshes.com
% www.gereshes.com


%This deletes any existing coms objects
try
    delete(instrfindall); 
catch
end

recordTimeInMinutes = 15;%Your expected recording time in minutes
currentRunTime = 9.3500e-04;%Your expected sampling period in seconds(Depends on hardware, doesnt need to be exact)
s=serial('COM3') %Creates serial object. You may need to change this depending on the port you're using
set(s,'BaudRate',115200) %Sets baud rate
fopen(s); %Opens the serial port
samples = ceil((60*recordTimeInMinutes)/currentRunTime); % number of samples
holder=zeros(2,samples); %initializes the holder matrix
holderCell = cell(1,samples);
flushinput(s) %Flush the input buffer
for p=1:samples   
    try
        holderCell{p}=fgetl(s); %Gets the data from the serial port and then writes it to the holder cell
    catch
    end
end


