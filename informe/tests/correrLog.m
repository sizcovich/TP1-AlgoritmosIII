function [res] = correrLog(input)
n = size(input);
res = zeros(size(input));
for i=1:n
    m = i*log(i);
    res(i) = m;
end
end

