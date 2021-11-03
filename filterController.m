% controller


% low-pass filter: for initial force
tau = 0.5;
forceLPF = tf([1], [tau,1]);
% forceLPF = 1;
sensorLPF = tf(1, [tau,1]);
windLPF = tf(1, [30,1]);

speedLPF4Ctrl = tf(1,[10,1]);



% torque controller design
hubBearingDamp = 1e2;
omega_speed = 0.5;
Ki_speed = omega_speed^2*rotor.I(3);
Kp_speed = 2*omega_speed*rotor.I(3)-hubBearingDamp;
omgM = 0.5*rotor.ratedSpeed;
cut_in = 3;
rotor.minSpeed = tipRatioOpt * cut_in / rotor.R;

% gain scheduling pitch
% definition of a 5-MW .... by Jonkman
windspeedlist = [11.4 12:1:25];
pitchlist = [0 3.83 6.6 8.7 10.45 12.06 13.54 14.92 16.23 17.47 18.7 19.94 21.18 22.35 23.47];
dP_dtheta = -[28.24 43.73 51.66 58.44 64.44 70.46 76.53 83.94 90.67 94.71 99.04 105.90 114.3 120.2 125.3]*1e6;

theta_k = 8.7;
zeta_phi = 1.0;
omega_phi = 4;

Kp_pitch = 2*rotor.I(3)*rotor.ratedSpeed*zeta_phi*omega_phi/(-dP_dtheta(1));
Ki_pitch = rotor.I(3)*rotor.ratedSpeed*omega_phi^2/(-dP_dtheta(1));




