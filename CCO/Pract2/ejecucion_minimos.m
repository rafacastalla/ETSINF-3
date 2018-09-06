%Sacar_Minimos(y,u,na,nb,d, H)
Sacar_Minimos(Vel2,u2,1,1,1, 7)
Sacar_Minimos(Vel2,u2,2,1,1, 7)
Sacar_Minimos(Vel2,u2,2,2,1, 7)
Sacar_Minimos(Vel2,u2,3,3,1, 7)


Comprobar_modelo([-0.9596],[0.0359],0.01)
Comprobar_modelo([-1.3459, 0.3805],[0.0117,0.0190],0.01)
%H=0
Comprobar_modelo([-1.3491, 0.3840],[0.0119,0.0190],0.01)

Comprobar_modelo([-0.8256, -0.4255,0.3009],[0.0125,0.0227,0.0089],0.01)

%%Para Vel1 y U1
Comprobar_modelo([-0.9423],[0.0567],0.01)
Sacar_Minimos(Vel1,u1,1,1,1, 0)