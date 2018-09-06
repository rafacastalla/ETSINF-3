function [error] = Ini_tarjetas2()
%**********************************************************
% Iniciar uso de Tarjetas
%**********************************************************
global cardID PCI_9112; error=0; warning off;

%Carga las lib's (si es necesario)
if (libisloaded('PCIDask')~=1), loadlibrary('PCIDask', 'Dask.h'); end;

%Visualización de las funciones disponibles
%libfunctions ('PCIDask', '-full');

%Inicializar la tarjeta PCI-9112
cardID=calllib('PCIDask','Register_Card', PCI_9112, 0);
if cardID<0
    error=1;    disp('Ha ocurrido un error (Register_Card). Tarjeta NO 9112 inicializada');
    cardID
end

%Configurar el canal de salida
err=calllib('PCIDask','AO_9112_Config', cardID, 0, -10.0);
if err~=0
    error=1;    disp('Ha ocurrido un error (AO_9112_Config). Tarjeta NO 9112 inicializada');
    err
end