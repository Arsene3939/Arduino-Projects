while(1):
    x=[int(i)/255 for i in input().split(',')]
    if x=="exit":
        break
    ma=max(x)
    mi=min(x)
    if ma==mi:
        h=0
    elif ma==x[0] and x[1]>=x[2]:
        h=60*(x[1]-x[2])/(ma-mi)
    elif ma==x[0] and x[1]<x[2]:
        h=60*(x[1]-x[2])/(ma-mi)+360
    elif ma==x[1]:
        h=60*(x[2]-x[0])/(ma-mi)+120
    elif ma==x[2]:
        h=60*(x[0]-x[1])/(ma-mi)+240
    h=int(h/360*255)
    v=int(ma*255)
    s=1-mi/ma
    s=(int(s*255))
    ss=[h,s,v]
    print(ss)