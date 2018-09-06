function com = Comprobar_modelo(a,b,tt)

%**********************************************************
% OBTENCION SALIDA DE UN MODELO
%**********************************************************

%**********************************************************
%  PERIODO DE MUESTREO T
T= tt;
%caso 1%
a1 =0;
b1 = 0;
%caso 2
a2 =  0;
b2 =  0;
%caso 3 
a3 = 0;
b3 = 0;
 
na=length(a);
nb=length(b);

 if (na==1)
     a1=a(1);
 elseif (na==2)
     a1=a(1);
     a2=a(2);
 elseif (na==3)
     a1=a(1);
     a2=a(2);   
     a3=a(3);
 end;
 
  if (nb==1)
     b1=b(1);
 elseif (nb==2)
     b1=b(1);
     b2=b(2);
 elseif (na==3)
     b1=b(1);
     b2=b(2);   
     b3=b(3);
 end;
   
%Formula 
%Res=(inv(F'*F))*F'*Y
%**********************************************************
%Inicializar Variables
MUEST=1000; y=[]; error=[]; u=[]; t=[];

% Fijando una entrada al modelo Escalon 
% Mismo Valor el valor Escalon utilizado en la version real
% Nuestro caso utilizamos Prueba.m(motor real) Escalon de 2
u=ones(1,MUEST+1)*2;

%Modelo valido para 1 1 / 2 2 / 3 3
%Bucle de Generación de Datos
for i=1:MUEST+1
    
    % Almacenar valor del instante actual
    t(i)=((i-1)*T);
    
    %Calculo Salida Bucle Abierto caso 1
    if (na==1|| nb==1 )
        if (i==1) y(i)=0;
        else y(i)=-a1*y(i-1)+b1*u(i-1);
        end;
    elseif(na==2 || nb==2 )
        %Calculo Salida Bucle Abierto caso 2
         if (i==1) y(i)=0;
         elseif (i==2) y(i)=-a1*y(i-1)+b1*u(i-1);
         else y(i)=-a1*y(i-1)-a2*y(i-2)+b1*u(i-1)+b2*u(i-2);
         end;
   elseif(na==3 || nb==3)
%Calculo Salida Bucle Abierto caso 2
     if(i==1) y(i)=0;
     elseif (i==2) y(i)=-a1*y(i-1)+b1*u(i-1);
     elseif (i==3) y(i)=-a1*y(i-1)-a2*y(i-2)+b1*u(i-1)+b2*u(i-2);
     else y(i)=-a1*y(i-1)-a2*y(i-2)-a3*y(i-3)+b1*u(i-1)+b2*u(i-2)+b3*u(i-3);
     end;
     
   end;     
       
end;

% Almacenar datos en un fichero de texto
t=t'; y=y'; u=u';
% Salida y(k):= Velocidad SIMULADA del motor debe ser muy parecida a la
% velocidad real del motor Vel1
figure;
plot(t,y); %simulat comparem amb el real, deu de ser paregut
% hold;
% plot(t1,Vel1,'g');
figure;
plot(t,u,'r');
% hold;
% plot(t,u1,'g');
end