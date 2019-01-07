function rst=BaseFunction(k,m,t,KnotVector)
if m==1
    if t>=KnotVector(k) && t<KnotVector(k+1)
        rst=1;
    else
        rst=0;
    end
else
    if KnotVector(k+m-1)~= KnotVector(k)
        c1=(t-KnotVector(k))/(KnotVector(k+m-1)-KnotVector(k));
    else
        c1=0;
    end
    if KnotVector(k+m)~=KnotVector(k+1)
        c2=(KnotVector(k+m)-t)/(KnotVector(k+m)-KnotVector(k+1));
    else
        c2=0;
    end    
    rst=c1*BaseFunction(k,m-1,t,KnotVector)+c2*BaseFunction(k+1,m-1,t,KnotVector);
end