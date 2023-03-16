% Programa para el giroscopio con Arduino
clear all
clc

s = serialport("COM6", 9600, "Timeout", 5);     % Inicializa el puerto serie

test = zeros(100, 6);       % Matriz para almacenar 6 columnas

for i = 1: 101
    for j = 1: 6
        data = readline(s);
        test(i,j) = data;
    end
end

avg = zeros(1, 6);

for k = 1: 100
    for h = 1: 6
        sum(1,h) =+ test(k,h);
    end
end

avg()