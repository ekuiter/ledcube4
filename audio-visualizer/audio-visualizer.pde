import processing.serial.*;
import java.awt.*;
 
//Eingabe
Serial myPort;
String input;
 
PFont font;
 
int a,b,c,d,e,f,h;
 
int positionA = 0;
int positionB = 0;
int positionC = 0;
int positionD = 0;
int positionE = 0;
int positionF = 0;
int positionG = 0;
 
FrameA f_a;
FrameB f_b;
FrameC f_c;
FrameD f_d;
FrameE f_e;
FrameF f_f;
FrameG f_g;
GraphA graphA;
GraphB graphB;
GraphC graphC;
GraphD graphD;
GraphE graphE;
GraphF graphF;
GraphG graphG;
 
/*void setup() {
  println(Serial.list());
}*/
 
void setup()
{
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
  //Erstes Einlesen wegwerfen
  input = myPort.readStringUntil('\n');
  input =null;
  //Schriftart laden muss sich im Ordner data befinden
  font = loadFont("CourierNew36.vlw");
 
  //2 weitere Fenster erstellen
  f_a = new FrameA();
  f_b = new FrameB();
  f_c = new FrameC();
  f_d = new FrameD();
  f_e = new FrameE();
  f_f = new FrameF();
  f_g = new FrameG();
  size(400,800);
  background(0);
  smooth();
}

void draw()
{
  einlesen_Daten();
}
 
void einlesen_Daten()
{
  //Daten einlesen bis zum newLine
  input = myPort.readStringUntil('\n');
  if(input!=null)
  {
    //Leerzeichen entfernen    
    input = input.trim();
    //Werte trennen
    int [] values = int(input.split(","));
    //Anpassen an die Anzahl von Sensoren, die man verwendet.
    if(values.length == 7)
    {
      a = values[0];
      b = values[1];
      c = values[2];
      d = values[3];
      e = values[4];
      f = values[5];
      h = values[6];
    }
  }
}
 
public class FrameA extends Frame
{
  public FrameA()
  {
        setBounds(0,0,180,600);
        graphA = new GraphA();
        add(graphA);
        graphA.init();
        show();
  }
}
public class FrameB extends Frame
{
  public FrameB()
  {
        setBounds(0,0,180,600);
        graphB = new GraphB();
        add(graphB);
        graphB.init();
        show();
  }
}
public class FrameC extends Frame
{
  public FrameC()
  {
        setBounds(0,0,180,600);
        graphC = new GraphC();
        add(graphC);
        graphC.init();
        show();
  }
}
public class FrameD extends Frame
{
  public FrameD()
  {
        setBounds(0,0,180,600);
        graphD = new GraphD();
        add(graphD);
        graphD.init();
        show();
  }
}
public class FrameE extends Frame
{
  public FrameE()
  {
        setBounds(0,0,180,600);
        graphE = new GraphE();
        add(graphE);
        graphE.init();
        show();
  }
}
public class FrameF extends Frame
{
  public FrameF()
  {
        setBounds(0,0,180,600);
        graphF = new GraphF();
        add(graphF);
        graphF.init();
        show();
  }
}
public class FrameG extends Frame
{
  public FrameG()
  {
        setBounds(0,0,180,600);
        graphG = new GraphG();
        add(graphG);
        graphG.init();
        show();
  }
}
public class GraphA extends PApplet
{
 
    public void setup()
    {
        size(180, 600);
        smooth();
        background(0);
    }
    public void draw()
    {
      fill(0);
      rect(0,0,500,100);
      stroke(255,0,0);
      line(positionA, height, positionA, height-a);
      fill(255,0,0);
      textFont(font, 30);
      text("1 = "+a,20,20);
      noStroke();
      noFill();
      if (positionA >= width-2)
      {
        positionA = 0;
        background(0);
      }
      else
      {
        positionA++;
      }
    }
}
public class GraphB extends PApplet
{
 
    public void setup()
    {
        size(180, 600);
        smooth();
        background(0);
    }
    public void draw()
    {
      fill(0);
      rect(0,0,500,100);
      stroke(255,0,0);
      line(positionB, height, positionB, height-b);
      fill(255,0,0);
      textFont(font, 30);
      text("2 = "+b,20,20);
      noStroke();
      noFill();
      if (positionB >= width-2)
      {
        positionB = 0;
        background(0);
      }
      else
      {
        positionB++;
      }
    }
}
public class GraphC extends PApplet
{
 
    public void setup()
    {
        size(180, 600);
        smooth();
        background(0);
    }
    public void draw()
    {
      fill(0);
      rect(0,0,500,100);
      stroke(255,0,0);
      line(positionC, height, positionC, height-c);
      fill(255,0,0);
      textFont(font, 30);
      text("3 = "+c,20,20);
      noStroke();
      noFill();
      if (positionC >= width-2)
      {
        positionC = 0;
        background(0);
      }
      else
      {
        positionC++;
      }
    }
}
public class GraphD extends PApplet
{
 
    public void setup()
    {
        size(180, 600);
        smooth();
        background(0);
    }
    public void draw()
    {
      fill(0);
      rect(0,0,500,100);
      stroke(255,0,0);
      line(positionD, height, positionD, height-d);
      fill(255,0,0);
      textFont(font, 30);
      text("4 = "+d,20,20);
      noStroke();
      noFill();
      if (positionD >= width-2)
      {
        positionD = 0;
        background(0);
      }
      else
      {
        positionD++;
      }
    }
}
public class GraphE extends PApplet
{
 
    public void setup()
    {
        size(180, 600);
        smooth();
        background(0);
    }
    public void draw()
    {
      fill(0);
      rect(0,0,500,100);
      stroke(255,0,0);
      line(positionE, height, positionE, height-e);
      fill(255,0,0);
      textFont(font, 30);
      text("5 = "+e,20,20);
      noStroke();
      noFill();
      if (positionE >= width-2)
      {
        positionE = 0;
        background(0);
      }
      else
      {
        positionE++;
      }
    }
}
public class GraphF extends PApplet
{
 
    public void setup()
    {
        size(180, 600);
        smooth();
        background(0);
    }
    public void draw()
    {
      fill(0);
      rect(0,0,500,100);
      stroke(255,0,0);
      line(positionF, height, positionF, height-f);
      fill(255,0,0);
      textFont(font, 30);
      text("6 = "+f,20,20);
      noStroke();
      noFill();
      if (positionF >= width-2)
      {
        positionF = 0;
        background(0);
      }
      else
      {
        positionF++;
      }
    }
}
public class GraphG extends PApplet
{
 
    public void setup()
    {
        size(180, 600);
        smooth();
        background(0);
    }
    public void draw()
    {
      fill(0);
      rect(0,0,500,100);
      stroke(255,0,0);
      line(positionG, height, positionG, height-h);
      fill(255,0,0);
      textFont(font, 30);
      text("7 = "+h,20,20);
      noStroke();
      noFill();
      if (positionG >= width-2)
      {
        positionG = 0;
        background(0);
      }
      else
      {
        positionG++;
      }
    }
}
