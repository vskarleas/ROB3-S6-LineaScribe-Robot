function angles = input(x,y,L1,L2)

% dteta = asin((x^2+y^2-L1^2-L2^2)/(2*L1*L2))
% teta1 = atan(y/x) - atan((-L2*cos(dteta))/(L1+L2*sin(dteta)))
% teta2=dteta+teta1

% teta2prec = acos((x^2+y^2-L1^2-L2^2)/(2*L1*L2))
% teta1 = atan(y/x) - atan((L2*sin(teta2prec))/(L1+L2*cos(teta2prec)))
% if teta1<=0
%     teta1=-teta1
% end

% teta2=teta2prec-teta1-var
% 

% teta2 = acos((x^2+y^2-L1^2-L2^2)/(2*L1*L2))
% teta1 = atan(y/x) - atan((L2*sin(teta2))/(L1+L2*cos(teta2)))
% rad2deg(teta2prec)

%% CODE FONCTIONNEL:

co2 = (x^2+y^2-L1^2-L2^2)/(2*L1*L2)
teta2prec = atan2((-sqrt(1-co2^2)),co2)

teta1 = atan2(y,x) - atan2((L2*sin(teta2prec)),(L1+L2*cos(teta2prec)))

rad2deg(teta2prec)
rad2deg(teta1)


teta2=-abs(teta2prec)+teta1+pi



% if teta1<0
%     teta1=-teta1
%     teta2prec=-teta2prec
% end
% 
% dteta=teta2prec-teta1
% 
% if dteta<0
%     dteta=-dteta
% end
% 
% teta2=dteta-pi/2

angles = [rad2deg(teta1) rad2deg(teta2)];