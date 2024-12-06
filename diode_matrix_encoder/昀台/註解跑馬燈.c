//重點看 第763行void led_print(char string[])的程式 
#define t 200//跑馬燈速度 
int LEDC[8]={16,25,26,2,14,0,5,18};//腳位 
int LEDL[8]={27,23,12,32,4,13,17,15};;//腳位 
int i=0,j=0;
//c:x,l:y
void turnlightalloff()//關燈函數 
{
  for(int i=0;i<8;i++) {
  	digitalWrite(LEDC[i],1);
  	digitalWrite(LEDL[i],0);
  } 
}
void light(int x,int y)//點燈函數 
{ 
  if(x>7||y>7||x<0||y<0)return;
  turnlightalloff();
  for(int i=0;i<50;i++){
    digitalWrite(LEDL[y],1);
    digitalWrite(LEDC[x],0);
  }
}
void lightsquare(int x,int y,int X,int Y)
{
  for(int i=x;i<=X;i++)
  for(int j=y;j<=Y;j++)
  {
      light(i,j);
  }
}
void line(int x,int y,int X){
  if(x>X)
  for(int i=x;i>=X;i--)
  {
    light(i,y);
    y++;
  }
  if(X>x)
  for(int i=x;i<=X;i++)
  {
    light(i,y);
    y++;
  }
}
void lightbox(int x,int y,int X,int Y)
{
    for(int i=x;i<=X;i++)
    {
      light(i,y);
      light(i,Y);
    }
    for(int j=y+1;j<=Y-1;j++)
    {
      light(x,j);
      light(X,j);
    }
}
void turnofflight(int x,int y)
{
  digitalWrite(LEDL[y],0);
  digitalWrite(LEDC[x],1);
}
void turnofflightsquare(int x,int y,int X,int Y)
{
  for(int i=x;i<=X;i++)
  for(int j=y;j<=Y;j++)
  {
      turnofflight(i,j);
  }
}
void zero(int c=0,int l=0)
{
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(3+c,1+l,4+c,1+l);
    lightsquare(5+c,2+l,5+c,6+l);
    lightsquare(2+c,2+l,2+c,6+l);
    lightsquare(3+c,7+l,4+c,7+l);
}
void one(int c=0,int l=0)
{
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(4+c,2+l,4+c,7+l);
    light(3+c,6+l);
    lightsquare(3+c,1+l,5+c,1+l);
}
void two(int c=0,int l=0)
{
  if(c>5||l>7||c<-6||l<0)return; 
    light(2+c,6+l);
    light(3+c,2+l);
    light(4+c,3+l);
    light(3+c,7+l);
    light(4+c,7+l);
    lightsquare(5+c,4+l,5+c,6+l);
    lightsquare(2+c,1+l,5+c,1+l);
}
void three(int c=0,int l=0)
{
  if(c>5||l>7||c<-6||l<0)return; 
    light(3+c,4+l);
    light(4+c,4+l);
    lightsquare(3+c,7+l,4+c,7+l);
    lightsquare(5+c,5+l,5+c,6+l);
    lightsquare(3+c,1+l,4+c,1+l);
    lightsquare(5+c,2+l,5+c,3+l);
    light(2+c,2+l);
    light(2+c,6+l);
}
void four(int c=0,int l=0)
{
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(5+c,1+l,5+c,7+l);
    line(2+c,4+l,4+c);
    lightsquare(2+c,3+l,4+c,3+l);
    light(6+c,3+l);
}
void five(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(3+c,1+l,4+c,1+l);
    lightsquare(5+c,2+l,5+c,4+l);
    light(2+c,2+l);
    lightsquare(2+c,5+l,4+c,5+l);
    light(2+c,6+l);
    lightsquare(2+c,7+l,5+c,7+l);
}
void six(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(3+c,1+l,4+c,1+l);
    lightsquare(5+c,2+l,5+c,3+l);
    lightsquare(2+c,2+l,2+c,6+l);
    lightsquare(3+c,4+l,4+c,4+l);
    lightsquare(3+c,7+l,4+c,7+l);
    light(5+c,6+l);
}
void seven(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    light(2+c,6+l);
    light(2+c,7+l);
    lightsquare(3+c,7+l,5+c,7+l);
    light(5+c,5+l);
    light(5+c,6+l);
    light(4+c,1+l);
    light(4+c,2+l);
    light(4+c,3+l);
    light(4+c,4+l);
}
void eight(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(3+c,1+l,4+c,1+l);
    lightsquare(5+c,2+l,5+c,3+l);
    lightsquare(2+c,2+l,2+c,3+l);
    lightsquare(2+c,5+l,2+c,6+l);
    lightsquare(3+c,4+l,4+c,4+l);
    lightsquare(3+c,7+l,4+c,7+l);
    lightsquare(5+c,5+l,5+c,6+l);
}
void nine(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(2+c,5+l,2+c,6+l);
    lightsquare(3+c,4+l,4+c,4+l);
    lightsquare(3+c,7+l,4+c,7+l);
    lightsquare(3+c,1+l,4+c,1+l);
    lightsquare(5+c,2+l,5+c,6+l);
    light(2+c,2+l);
}
void Af(int c=0,int l=0)
{
  if(c>5||l>7||c<-6||l<0)return; 
    light(4+c,7+l);
    light(3+c,6+l);
    light(5+c,6+l);
    light(2+c,5+l);
    light(6+c,5+l);
    lightsquare(2+c,1+l,2+c,4+l);
    lightsquare(6+c,1+l,6+c,4+l);
    lightsquare(3+c,3+l,5+c,3+l);
}
void Bf(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(2+c,1+l,2+c,7+l);
    lightsquare(3+c,1+l,5+c,1+l);
    lightsquare(3+c,4+l,5+c,4+l);
    lightsquare(3+c,7+l,5+c,7+l);
    light(6+c,2+l);
    light(6+c,3+l);
    light(6+c,5+l);
    light(6+c,6+l);
}
void Cf(int c=0,int l=0)
{
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(2+c,2+l,2+c,6+l);
    lightsquare(3+c,1+l,5+c,1+l);
    lightsquare(3+c,7+l,5+c,7+l);
    light(6+c,2+l);
    light(6+c,6+l);
}
void Df(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(2+c,1+l,2+c,7+l);
    lightsquare(6+c,3+l,6+c,5+l);
    light(5+c,2+l);
    light(5+c,6+l);
    light(4+c,1+l);
    light(3+c,1+l);
    light(4+c,7+l);
    light(3+c,7+l);
}
void Ef(int c=0,int l=0)
{
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(2+c,1+l,6+c,1+l);
    lightsquare(2+c,7+l,6+c,7+l);
    lightsquare(2+c,2+l,2+c,6+l);
    lightsquare(3+c,4+l,5+c,4+l);
}
void Ff(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(2+c,7+l,6+c,7+l);
    lightsquare(2+c,1+l,2+c,6+l);
    lightsquare(3+c,4+l,5+c,4+l);
}
void Gf(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(2+c,2+l,2+c,6+l);
    lightsquare(3+c,7+l,5+c,7+l);
    lightsquare(3+c,1+l,5+c,1+l);
    lightsquare(4+c,4+l,6+c,4+l);
    light(6+c,6+l);
    light(6+c,2+l);
    light(6+c,3+l);
}
void Hf(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(2+c,1+l,2+c,7+l);
    lightsquare(6+c,1+l,6+c,7+l);
    lightsquare(3+c,4+l,5+c,4+l);
}
void If(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
  for(int i=0;i<2;i++){
    light(3+c,7+l);
    light(5+c,7+l);
    light(3+c,1+l);
    light(5+c,1+l);
    lightsquare(4+c,1+l,4+c,7+l);
  }
}
void Jf(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(5+c,2+l,5+c,6+l);
    lightsquare(4+c,7+l,6+c,7+l);
    light(2+c,2+l);
    light(3+c,1+l);
    light(4+c,1+l);
}
void Kf(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(2+c,1+l,2+c,7+l);
    line(3+c,4+l,6+c);
    line(6+c,1+l,4+c);
}
void Lf(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(2+c,1+l,2+c,7+l);
    lightsquare(3+c,1+l,6+c,1+l);
}
void Mf(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(2+c,1+l,2+c,7+l);
    lightsquare(6+c,1+l,6+c,7+l);
    lightsquare(4+c,4+l,4+c,5+l);
    light(3+c,6+l);
    light(5+c,6+l);
}
void Nf(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(2+c,1+l,2+c,7+l);
    lightsquare(6+c,1+l,6+c,7+l);
    line(5+c,3+l,3+c);
}
void Of(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(2+c,2+l,2+c,6+l);
    lightsquare(3+c,1+l,5+c,1+l);
    lightsquare(6+c,2+l,6+c,6+l);
    lightsquare(3+c,7+l,5+c,7+l);
}
void Pf(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(2+c,1+l,2+c,7+l);
    lightsquare(3+c,4+l,5+c,4+l);
    lightsquare(3+c,7+l,5+c,7+l);
    light(6+c,6+l);
    light(6+c,5+l);
}
void Qf(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(2+c,2+l,2+c,6+l);
    lightsquare(3+c,1+l,4+c,1+l);
    lightsquare(6+c,3+l,6+c,6+l);
    lightsquare(3+c,7+l,5+c,7+l);
    line(6+c,1+l,4+c);
}
void Rf(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(2+c,1+l,2+c,7+l);
    lightsquare(3+c,4+l,5+c,4+l);
    lightsquare(3+c,7+l,5+c,7+l);
    light(6+c,6+l);
    light(6+c,5+l);
    line(6+c,1+l,4+c);
}
void Sf(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(2+c,1+l,5+c,1+l);
    lightsquare(3+c,4+l,5+c,4+l);
    lightsquare(3+c,7+l,6+c,7+l);
    light(2+c,5+l);
    light(2+c,6+l);
    light(6+c,2+l);
    light(6+c,3+l);
}
void Tf(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(2+c,7+l,6+c,7+l);
    lightsquare(4+c,1+l,4+c,6+l);
}
void Uf(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(2+c,2+l,2+c,7+l);
    lightsquare(6+c,2+l,6+c,7+l);
    lightsquare(3+c,1+l,5+c,1+l);
}
void Vf(int c=0,int l=0)
{
  if(c>5||l>7||c<-6||l<0)return; 
    light(4+c,1+l);
    lightsquare(2+c,3+l,2+c,7+l);
    lightsquare(6+c,3+l,6+c,7+l);
    lightsquare(3+c,2+l,3+c,3+l);
    lightsquare(5+c,2+l,5+c,3+l);
}
void Wf(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(2+c,2+l,2+c,7+l);
    lightsquare(6+c,2+l,6+c,7+l);
    lightsquare(4+c,2+l,4+c,5+l);
    light(3+c,1+l);
    light(5+c,1+l);
}
void Xf(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    line(2+c,2+l,6+c);
    line(6+c,2+l,5+c);
    line(3+c,5+l,2+c);
    light(2+c,1+l);
    light(2+c,7+l);
    light(6+c,7+l);
    light(6+c,1+l);
}
void Yf(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return;  
    lightsquare(2+c,5+l,2+c,7+l);
    lightsquare(6+c,5+l,6+c,7+l);
    lightsquare(4+c,1+l,4+c,3+l);
    light(3+c,4+l);
    light(5+c,4+l);
}
void Zf(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(2+c,7+l,6+c,7+l);
    lightsquare(2+c,1+l,6+c,1+l);
    line(2+c,2+l,6+c);
}
void af(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(3+c,1+l,5+c,1+l);
    lightsquare(3+c,3+l,5+c,3+l);
    lightsquare(3+c,5+l,5+c,5+l);
    lightsquare(6+c,1+l,6+c,4+l);
    light(2+c,2+l);
}
void bf(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(2+c,1+l,2+c,7+l);
    lightsquare(3+c,1+l,5+c,1+l);
    lightsquare(6+c,2+l,6+c,4+l);
    light(3+c,4+l);
    light(5+c,5+l);
    light(4+c,5+l);
}
void cf(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(3+c,5+l,5+c,5+l);
    lightsquare(3+c,1+l,5+c,1+l);
    lightsquare(2+c,2+l,2+c,4+l);
    light(6+c,2+l);
}
void df(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return;
    lightsquare(2+c+4,1+l,2+4+c,7+l);
    lightsquare(3+c,1+l,5+c,1+l);
    lightsquare(6-4+c,2+l,6-4+c,4+l);
    light(5+c,4+l);
    light(4+c,5+l);
    light(3+c,5+l);
}
void ef(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(3+c,1+l,5+c,1+l);
    lightsquare(3+c,3+l,6+c,3+l);
    lightsquare(3+c,5+l,5+c,5+l);
    lightsquare(2+c,2+l,2+c,4+l);
    light(6+c,4+l);
}
void ff(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(3+c,1+l,3+c,6+l);
    light(6+c,6+l);
    light(5+c,7+l);
    light(4+c,7+l);
    light(2+c,4+l);
    light(4+c,4+l);
}
void gf(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return;   
    lightsquare(3+c,1+l,5+c,1+l);
    lightsquare(3+c,3+l,5+c,3+l);
    lightsquare(3+c,6+l,5+c,6+l);
    lightsquare(6+c,2+l,6+c,6+l);
    light(2+c,4+l);
    light(2+c,5+l);
}
void hf(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(2+c,1+l,2+c,7+l);
    lightsquare(6+c,1+l,6+c,4+l);
    light(3+c,4+l);
    light(4+c,5+l);
    light(5+c,5+l);
}
void iF(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(4+c,1+l,4+c,5+l);
    light(3+c,5+l);
    light(4+c,7+l);
    light(3+c,1+l);
    light(5+c,1+l);
}
void jf(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    light(5+c,7+l);
    light(2+c,2+l);
    light(3+c,1+l);
    light(4+c,1+l);
    light(4+c,5+l);
    lightsquare(5+c,2+l,5+c,5+l);
}
void kf(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(2+c,1+l,2+c,7+l);
    line(3+c,3+l,5+c);
    light(4+c,2+l);
    light(5+c,1+l);
}
void lf(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(4+c,2+l,4+c,7+l);
    light(3+c,7+l);
    lightsquare(3+c,1+l,5+c,1+l);
}
void mf(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return;   
    lightsquare(2+c,1+l,2+c,5+l);
    lightsquare(6+c,1+l,6+c,4+l);
    light(3+c,5+l);
    light(5+c,5+l);
    light(4+c,4+l);
    light(4+c,3+l);
}
void nf(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return;    
    lightsquare(2+c,1+l,2+c,5+l);
    lightsquare(6+c,1+l,6+c,4+l);
    light(5+c,5+l);
    light(3+c,4+l);
    light(4+c,5+l);
}
void of(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(3+c,1+l,5+c,1+l);
    lightsquare(6+c,2+l,6+c,4+l);
    lightsquare(3+c,5+l,5+c,5+l);
    lightsquare(2+c,2+l,2+c,4+l);
}
void pf(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(2+c,1+l,2+c,5+l);
    lightsquare(3+c,3+l,5+c,3+l);
    lightsquare(3+c,5+l,5+c,5+l);
    light(6+c,4+l);
}
void qf(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(6+c,1+l,6+c,5+l);
    lightsquare(3+c,3+l,5+c,3+l);
    light(2+c,4+l);
    light(3+c,5+l);
    light(4+c,5+l);
    light(5+c,4+l);
}
void rf(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(2+c,1+l,2+c,5+l);
    light(3+c,4+l);
    light(5+c,5+l);
    light(4+c,5+l);
    light(6+c,4+l);
}
void sf(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(2+c,1+l,5+c,1+l);
    lightsquare(3+c,3+l,5+c,3+l);
    lightsquare(3+c,5+l,6+c,5+l);
    light(2+c,4+l);
    light(6+c,2+l);
}
void tf(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(3+c,2+l,3+c,7+l);
    light(4+c,1+l);
    light(4+c,5+l);
    light(2+c,5+l);
    light(6+c,2+l);
    light(5+c,1+l);
}
void uf(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(2+c,2+l,2+c,5+l);
    lightsquare(6+c,1+l,6+c,5+l);
    light(4+c,1+l);
    light(5+c,2+l);
    light(3+c,1+l);
}
void vf(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return; 
    lightsquare(2+c,3+l,2+c,5+l);
    lightsquare(6+c,3+l,6+c,5+l);
    light(4+c,1+l);
    light(5+c,2+l);
    light(3+c,2+l);
}
void wf(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return;
    lightsquare(2+c,2+l,2+c,5+l);
    lightsquare(6+c,2+l,6+c,5+l);
    light(3+c,1+l);
    light(5+c,1+l);
    light(4+c,2+l);
    light(4+c,3+l);
}
void xf(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return;    
    line(2+c,1+l,6+c);
    line(6+c,1+l,5+c);
    line(3+c,4+l,2+c);
}
void yf(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return;    
    lightsquare(3+c,1+l,5+c,1+l);
    lightsquare(6+c,2+l,6+c,5+l);
    lightsquare(3+c,3+l,5+c,3+l);
    light(2+c,4+l);
    light(2+c,5+l);
}
void zf(int c=0,int l=0){
  if(c>5||l>7||c<-6||l<0)return;    
    lightsquare(2+c,1+l,6+c,1+l);
    lightsquare(2+c,5+l,6+c,5+l);
    line(3+c,2+l,5+c);
}
void _1(int c=0,int l=0)//!
{
  if(c>5||l>7||c<-6||l<0)return; 
  for(int i=0;i<2;i++){
    lightsquare(4+c,4+l,4+c,7+l);
    light(4+c,1+l);
  }
}
void _2(int c=0,int l=0)//%
{
  if(c>5||l>7||c<-6||l<0)return;   
    line(2+c,2+l,6+c);
    lightsquare(2+c,6+l,3+c,7+l);
    lightsquare(5+c,1+l,6+c,2+l);
}
void _3(int c=0,int l=0)//&
{
  if(c>5||l>7||c<-6||l<0)return; 
    line(6+c,1+l,2+c);
    light(6+c,3+l);
    light(3+c,1+l);
    light(2+c,2+l);
    light(2+c,3+l);
    light(4+c,5+l);
    light(2+c,6+l);
    light(3+c,7+l);
    light(4+c,7+l);
    light(5+c,6+l);
}
void _4(int c=0,int l=0)//(
{
  if(c>5||l>7||c<-6||l<0)return; 
  for(int i=0;i<2;i++){
    line(3+c,5+l,5+c);
    line(5+c,1+l,3+c);
    light(3+c,4+l);
  }
}
void _5(int c=0,int l=0)//)
{
  if(c>5||l>7||c<-6||l<0)return; 
  for(int i=0;i<2;i++){
    line(3+c,1+l,5+c);
    line(5+c,5+l,3+c);
    light(5+c,4+l);
  }
}
void _6(int c=0,int l=0)//+
{
  if(c>5||l>7||c<-6||l<0)return; 
  for(int i=0;i<2;i++){
    lightsquare(2+c,4+l,6+c,4+l);
    light(4+c,2+l);
    light(4+c,3+l);
    light(4+c,5+l);
    light(4+c,6+l);
  }
}
void _7(int c=0,int l=0)//=
{
  if(c>5||l>7||c<-6||l<0)return; 
  for(int i=0;i<2;i++){
    lightsquare(2+c,5+l,6+c,5+l);
    lightsquare(2+c,3+l,6+c,3+l);
  }
}
void _8(int c=0,int l=0)//-
{
  if(c>5||l>7||c<-6||l<0)return; 
  for(int i=0;i<6;i++)
    lightsquare(3+c,4+l,5+c,4+l);
}
void _9(int c=0,int l=0)//~
{
  if(c>5||l>7||c<-6||l<0)return; 
  for(int i=0;i<7;i++){
    line(5+c,3+l,3+c);
    light(2+c,4+l);
    light(6+c,4+l);
  }
}
void _10(int c=0,int l=0)//?
{
  if(c>5||l>7||c<-6||l<0)return;  
    lightsquare(3+c,7+l,5+c,7+l);
    light(6+c,6+l);
    light(2+c,6+l);
    light(6+c,5+l);
    light(5+c,4+l);
    light(4+c,3+l);
    light(4+c,1+l);
}
void _11(int c=0,int l=0)//:
{
  if(c>5||l>7||c<-6||l<0)return;   
  for(int i=0;i<2;i++){
    lightsquare(3+c,5+l,4+c,6+l);
    lightsquare(3+c,2+l,4+c,3+l);
  }
}
void _12(int c=0,int l=0)//;
{
  if(c>5||l>7||c<-6||l<0)return;   
  for(int i=0;i<2;i++){ 
    lightsquare(3+c,5+l,4+c,6+l);
    light(3+c,3+l);
    light(4+c,2+l);
    light(4+c,3+l);
    light(3+c,1+l);
  }
}
void _13(int c=0,int l=0)//>
{
  if(c>5||l>7||c<-6||l<0)return;   
  for(int i=0;i<2;i++){
    line(3+c,1+l,6+c);
    line(5+c,5+l,3+c);
  }
}
void _14(int c=0,int l=0)//<
{
  if(c>5||l>7||c<-6||l<0)return;    
  for(int i=0;i<2;i++){
    line(2+c,4+l,5+c);
    line(5+c,1+l,3+c);
  }
}
void _15(int c=0,int l=0)//,
{
  if(c>5||l>7||c<-6||l<0)return;    
  for(int i=0;i<4;i++){
    lightsquare(4+c,3+l,5+c,3+l);
    light(5+c,2+l);
    light(4+c,1+l);
  }
}
void _16(int c=0,int l=0)//.
{
  if(c>5||l>7||c<-6||l<0)return;    
  for(int i=0;i<4;i++){
    lightsquare(4+c,1+l,5+c,2+l);
  }
}
void _17(int c=0,int l=0)//#
{
  if(c>5||l>7||c<-6||l<0)return;    
    lightsquare(3+c,1+l,3+c,7+l);
    lightsquare(5+c,1+l,5+c,7+l);
    light(2+c,5+l);
    light(4+c,5+l);
    light(6+c,5+l);
    light(2+c,3+l);
    light(4+c,3+l);
    light(6+c,3+l);
}
void heart0(){
  for(int i=0;i<t*2;i++){
    line(3,0,0);
    line(4,1,6);
    line(0,4,1);
    line(6,4,5);
    line(3,4,2);
    line(0,4,1);
    light(4,5);
  }
}
void heart1(){
  for(int i=0;i<t*1.6;i++){
    line(3,1,1);
    line(4,2,5);
    line(3,3,2);
    light(4,4);
  }
}
void heart2(){
  for(int i=0;i<t*1.35;i++){
    line(3,2,2);
    light(4,3);
  }
}
void led_print(char string[])
{
/*  
	一次是呼叫所有輸入的字元
	只是有些人超出範圍於是不執行
	以輸入字串0123來作範例 
*/ 
  int lenth=strlen(string)*6;//設定跑馬燈長度 ,一個字6格,此字串為24格 
  for(int C=5;C>-7-lenth;C--){//一開始先將字串右推5格,然後字元向左移動出現
/*
	字元函數範例 
  	void zero(int c=0,int l=0)
	{
  		if(c>5||l>7||c<-6||l<0)return;若超出範圍,則不執行函數 
    	lightsquare(3+c,1+l,4+c,1+l);移動座標 須改變c值,改變L則是向上下移動 
    	lightsquare(5+c,2+l,5+c,6+l);
    	lightsquare(2+c,2+l,2+c,6+l);
    	lightsquare(3+c,7+l,4+c,7+l);
	}
*/ 
    for(int i=0;i<t;i++){//計時迴圈 
      for(int count=0;count<strlen(string);count++){ //計次迴圈,要24次 
        switch(string[count])//會將0~3的函數一次性的迅速全部呼叫完畢 
          {
            case '0':
              zero(C+count*6,L);//count為0 string[count]才會叫到此case,每字6格 
              //此時坐標為5+0
              //二次執行for(int C=5;C>-7-lenth;C--)之後會慢慢遞減4+0,3+0...-1+0(超出範圍)  
              turnlightalloff();//關燈 
            break;
            case '1':
              one((C+count*6,L)//count為1 string[count]才會叫到此case,每字6格 
              //此時坐標為5+6(超出範圍) 
              //二次執行for(int C=5;C>-7-lenth;C--)4+6...-1+6(進入範圍)-2+6...-7+6(超出範圍)  
			  turnlightalloff();//關燈                                                    
            break;
            case '2':
              two(C+count*6,L);//count為2 string[count]才會叫到此case,每字6格
              //此時坐標為5+12(超出範圍) 
              //二次執行for(int C=5;C>-7-lenth;C--)4+12...-7+12(進入範圍),-8+12...-13+12(超出範圍)  
              turnlightalloff();//關燈 
            break;
            case '3':
              three(C+count*6,L);//count為3 string[count]才會叫到此case,每字6格
              //此時坐標為5+18(超出範圍) 
              //執行for(int C=5;C>-7-lenth;C--)4+18...-13+18(進入範圍),-15+18...-19+18(超出範圍)  
              turnlightalloff();//關燈 
            break;
            case '4':
              four(C+count*6,L);
              turnlightalloff();
            break;
            case '5':
              five(C+count*6,L);
              turnlightalloff();
            break;
            case '6':
              six(C+count*6,L);
              turnlightalloff();
            break;
            case '7':
              seven(C+count*6,L);
              turnlightalloff();
            break;
            case '8':
              eight(C+count*6,L);
              turnlightalloff();
            break;
            case '9':
              nine(C+count*6,L);
              turnlightalloff();
            break;
            case 'A':
              Af(C+count*6,L);
              turnlightalloff();
            break;
            case 'B':          
              Bf(C+count*6,L);
              turnlightalloff();
            break;
            case 'C':         
              Cf(C+count*6,L);
              turnlightalloff();
            break;
            case 'D':        
              Df(C+count*6,L);
              turnlightalloff();
            break;
            case 'E':          
              Ef(C+count*6,L);
              turnlightalloff();
            break;
            case 'F':          
              Ff(C+count*6,L);
              turnlightalloff();
            break;
            case 'G':          
              Gf(C+count*6,L);
              turnlightalloff();
            break;
            case 'H':         
              Hf(C+count*6,L);
              turnlightalloff();
            break;
            case 'I':         
              If(C+count*6,L);
              turnlightalloff();
            break;
            case 'J':          
              Jf(C+count*6,L);
              turnlightalloff();
            break;
            case 'K':         
              Kf(C+count*6,L);
              turnlightalloff();
            break;
            case 'L':         
              Lf(C+count*6,L);
              turnlightalloff();
            break;
            case 'M':          
              Mf(C+count*6,L);
              turnlightalloff();
            break;
            case 'N':          
              Nf(C+count*6,L);
              turnlightalloff();
            break;
            case 'O':          
              Of(C+count*6,L);
              turnlightalloff();
            break;
            case 'P':          
              Pf(C+count*6,L);
              turnlightalloff();
            break;
            case 'Q':          
              Qf(C+count*6,L);
              turnlightalloff();
            break;
            case 'R':          
              Rf(C+count*6,L);
              turnlightalloff();
            break;
            case 'S':        
              Sf(C+count*6,L);
              turnlightalloff();
            break;
            case 'T':          
              Tf(C+count*6,L);
              turnlightalloff();
            break;
            case 'U':         
              Uf(C+count*6,L);
              turnlightalloff();
            break;
            case 'V':          
              Vf(C+count*6,L);
              turnlightalloff();
            break;
            case 'W':          
              Wf(C+count*6,L);
              turnlightalloff();
            break;
            case 'X':          
              Xf(C+count*6,L);
              turnlightalloff();
            break;
            case 'Y':          
              Yf(C+count*6,L);
              turnlightalloff();
            break;
            case 'Z':       
              Zf(C+count*6,L);
              turnlightalloff();
            break;
            case 'a':         
              af(C+count*6,L);
              turnlightalloff();
            break;
            case 'b':          
              bf(C+count*6,L);
              turnlightalloff();
            break;
            case 'c':          
              cf(C+count*6,L);
              turnlightalloff();
            break;
            case 'd':          
              df(C+count*6,L);
              turnlightalloff();
            break;
            case 'e':
              ef(C+count*6,L);
              turnlightalloff();
            break;
            case 'f':
              ff(C+count*6,L);
              turnlightalloff();
            break;
            case 'g':
              gf(C+count*6,L);
              turnlightalloff();
            break;
            case 'h':
              hf(C+count*6,L);
              turnlightalloff();
            break;
            case 'i':
              iF(C+count*6,L);
              turnlightalloff();
            break;
            case 'j':
              jf(C+count*6,L);
              turnlightalloff();
            break;
            case 'k':
              kf(C+count*6,L);
              turnlightalloff();
            break;
            case 'l':
              lf(C+count*6,L);
              turnlightalloff();
            break;
            case 'm':
              mf(C+count*6,L);
              turnlightalloff();
            break;
            case 'n':          
              nf(C+count*6,L);
              turnlightalloff();
            break;
            case 'o':          
              of(C+count*6,L);
              turnlightalloff();
            break;
            case 'p':        
              pf(C+count*6,L);
              turnlightalloff();
            break;
            case 'q':          
              qf(C+count*6,L);
              turnlightalloff();
            break;
            case 'r':          
              rf(C+count*6,L);
              turnlightalloff();
            break;
            case 's':          
              sf(C+count*6,L);
              turnlightalloff();
            break;
            case 't':         
              tf(C+count*6,L);
              turnlightalloff();
            break;
            case 'u':         
              uf(C+count*6,L);
              turnlightalloff();
            break;
            case 'v':         
              vf(C+count*6,L);
              turnlightalloff();
            break;
            case 'w':          
              wf(C+count*6,L);
              turnlightalloff();
            break;
            case 'x':          
              xf(C+count*6,L);
              turnlightalloff();
            break;
            case 'y':          
              yf(C+count*6,L);
              turnlightalloff();
            break;
            case 'z':          
              zf(C+count*6,L);
              turnlightalloff();
            break;
            case '!':
              _1(C+count*6,L);
              turnlightalloff();
            break;
            case '%':
              _2(C+count*6,L);
              turnlightalloff();
            break;
            case '&':
              _3(C+count*6,L);
              turnlightalloff();
            break;
            case '(':
              _4(C+count*6,L);
              turnlightalloff();
            break;
            case ')':
              _5(C+count*6,L);
              turnlightalloff();
            break;
            case '+':
              _6(C+count*6,L);
              turnlightalloff();
            break;
            case '=':
              _7(C+count*6,L);
              turnlightalloff();
            break;
            case '-':
              _8(C+count*6,L);
              turnlightalloff();
            break;
            case '~':
              _9(C+count*6,L);
              turnlightalloff();
            break;
            case '?':
              _10(C+count*6,L);
              turnlightalloff();
            break;
            case ':':
              _11(C+count*6,L);
              turnlightalloff();
            break;
            case ';':
              _12(C+count*6,L);
              turnlightalloff();
            break;
            case '>':
              _13(C+count*6,L);
              turnlightalloff();
            break;
            case '<':
              _14(C+count*6,L);
              turnlightalloff();
            break;
            case ',':
              _15(C+count*6,L);
              turnlightalloff();
            break;
            case '.':
              _16(C+count*6,L);
              turnlightalloff();
            break;
            case '#':
              _17(C+count*6,L);
              turnlightalloff();
            break;
            default:
            for(int i=0;i<15;i++)
              turnlightalloff();
             break;
          }
        }
      }
    }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int i=0;i<8;i++){
    pinMode(LEDC[i], OUTPUT);
    digitalWrite(LEDC[i],1);
  }
  for (int i=0;i<8;i++){
    pinMode(LEDL[i], OUTPUT);
    digitalWrite(LEDL[i],0);
  }
}
void loop() {
 led_print("0123");
 turnlightalloff();
 delay(1000);
}
