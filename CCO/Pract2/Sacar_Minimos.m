function tecta = Sacar_Minimos(y,u,na,nb,d, H)

    %**********************************************************
    % Parametros que recibimos en la llamada a función
    %**********************************************************
%     H = 1; %elementos iniciales de los vectores de entrada y salida que se quieren despreciar
%     na = 1; %numero de parametros incognita de a
%     nb = 1;%numero de parametros incognita de b
%     d = 1; %retardo del modelo
%     y = [0,0,0.25,0.375,-0.2625,-0.6812,0.1194,0.8547,0.0818,-0.8928]; %vector de salida
%     u = [0,0.5,1,0.5,0,0.5,1,0.5,0]; %vector de entrada

    %**********************************************************
    % Llenar matriz Y
    %**********************************************************
    
    %instante que garantiza que no hay ningun elemento con indice menor o igual que H
    M = H+1+max(na,nb-1+d); 
    %fprintf('Valor M = %f\n', M); 
    %longitud de mi vector y de entradas
    N = length(y);
    %fprintf('Valor N = %f\n', N);

    Y = []; %matriz Y

    for i=1:N-M
        Y = [Y;y(M+i)];

    end;

    %**********************************************************
    % Llenar matriz PHI
    %      [1 na 1 nb; 1 na 1 nb; 1 na 1 nb]
    % a = [1 2 3 33; 4 5 6 66; 7 8 10 1010]
    %**********************************************************
    PHI= []; %matriz phi
    vectora =[];
    vectorb =[];
    fila =[];

    for i=1:(N-M) %row y(M) - y(N)
        for j=1:na %col -y(M-1) - -y(M-na)
            vectora(j) = -1*y(M-j+i);
        end;
        for g=1:nb %col -y(M-1) - -y(M-na)
            vectorb(g) = u(M-d-g+1+i);
        end;
        fila = [vectora, vectorb];
        PHI = [PHI;fila];
    end;

%     disp('The result is Y:')
%     disp(Y)
%     disp('The result is PHI:')
%     disp(PHI)

    %**********************************************************
    % Calculo de los valores de a y b
    %**********************************************************

    tecta = inv(PHI'*PHI)*PHI'*Y;%Equacion de minimos cuadrados inv(phi'*phi)*phi'*Y
    fprintf('**********************\n');
    disp('The result is tecta:');
    disp(tecta);
    fprintf('');
end
