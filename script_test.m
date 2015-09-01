
fileName = 'imageFromBlackmagic.dpx';
iteration = 5000;

tic
for fileNo=1:iteration
  
    image=mexReadDPX16(fileName);
    disp(['Now reading ' num2str(fileNo) ' of ' num2str(iteration) ' image...']);
    
%     figure(1);clf
%     imshow(image);
%     drawnow

end
totalTime = toc;
[H,W,D] = size(image);

disp(['Everage reading time for ' ...
  num2str(H) 'x' num2str(W) 'x' num2str(D) ' image is about ' num2str(totalTime./iteration) 's']);