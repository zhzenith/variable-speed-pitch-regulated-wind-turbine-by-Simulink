%% WT parameters

% blade
blade.L = 61.5;
blade.m = 17740;
blade.com = [0 0 20.475];
blade.Ix = 11776047; % w.r.t root

%hub
hub.m = 56780;
hub.com = [0 0 0];
hub.Iz = 115926;

% rotor
rotor.m = 3*blade.m+hub.m;
rotor.com = [0 0 0];
rotor.Iz = 3*blade.Ix+hub.Iz;
rotor.Ix = blade.Ix*2;
rotor.Iy = rotor.Ix;
rotor.I = [rotor.Ix rotor.Iy rotor.Iz];
rotor.R=63;
rotor.Area = pi*rotor.R^2;
rotor.ratedSpeed=12.1*2*pi/60;


%nacelle
nacelle.m = 240000;
nacelle.dim = [4 4 13.8];
nacelle.com =[0 0 -6.5375]; % already considered in nacelle.dim
nacelle.I = [2607890 2607890 2607890/2];

% tower: OC3
tower.H = 87.6;
tower.topD = 3.87;
tower.baseD = 6.5;
tower.effR = (tower.topD+tower.baseD)/4;
tower.CoA = 2/5*tower.H; % center of aerodynamics;
tower.m = 249718; 
tower.com = [0 0 43.4];
tower.section = [0 0; tower.baseD/2 0; tower.topD/2 tower.H; 0 tower.H];
tower.I = tower.m*[40.05^2 40.05^2 2.70^2]; % w.r.t tower base
tower.clr = [0.8 0.8 0.8];
tower.cd = 1.2; % drag coef.

% aerodynamics
cpTable=xlsread('cp.xlsx');
ctTable=xlsread('ct.xlsx');
tipRatio=cpTable(2:21,1);
CpOpt = 0.482;
tipRatioOpt = 7.55;
beta=cpTable(1,2:37);
cpData=cpTable(2:21,2:37);
cpData = cpData*CpOpt/max(cpData(:));

CpOpt=max(cpData(:));
[idx,idy]=find(cpData==CpOpt);
tipRatio=tipRatio+(tipRatioOpt-tipRatio(idx));

ctData=ctTable(2:21,2:37);

%% 
wt.ratedPower = 5e6;
wt.ratedTorq = wt.ratedPower/rotor.ratedSpeed;