% run NREL5MW
% simulation using full model
rho_a = 1.225;
g=9.80665;

nrel5MW;
filterController;

% simulation conditions, book: wind turbine control systems--Fernando
% D.Bianchi, et al. 2007.
wind.alpha = 1e-6; % wind shear
wind.speed=11.4;
wind.direction=0; % in rad
a1=0.4;
a2=0.25;
Lv=180;
Tv=Lv/wind.speed;
Kv=sqrt(2*Tv*(1-a2^2)*(a1^2/a2-a2+1-a1^2)^(-1));
s=tf('s');
Hf=Kv*(Tv*a1*s+1)/((Tv*s+1)*(Tv*a2*s+1)); % turbulence model
sigmaV=0.14*wind.speed;

sim('windTurbine.slx');