function [res] = correrLog(input)
res = zeros(100,1);
i = 1000;
n = 1;
while i <= input
    m = log10(i);
    m = m * i;
    res(n,1) = m;
    i = i + 1000;
    n = n+1;
end
end

