 
#include <TimerOne.h>

#define S0     6
#define S1     5
#define S2     4
#define S3     3
#define OUT    2

int   g_count = 0;   
int   g_array[3];    
int   g_flag = 0;   
float g_SF[3];   
float sprt();
int VALUE, VALUE1, HUE, OSC, RB, BR, GBR;


 
void TSC_Init()
{
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(OUT, INPUT);
 
  digitalWrite(S0, LOW); 
  digitalWrite(S1, HIGH); 
}
 

void TSC_FilterColor(int Level01, int Level02)
{
  if(Level01 != 0)
    Level01 = HIGH;
 
  if(Level02 != 0)
    Level02 = HIGH;
 
  digitalWrite(S2, Level01); 
  digitalWrite(S3, Level02); 
}
 
void TSC_Count()
{
  g_count ++ ;
}
 
void TSC_Callback()
{
  switch(g_flag)
  {
    case 0: 
        
         TSC_WB(LOW, LOW);              
         break;
    case 1:

         g_array[0] = g_count;
         TSC_WB(HIGH, HIGH);            
         break;
    case 2:

         g_array[1] = g_count;
         TSC_WB(LOW, HIGH);          
         break;
 
    case 3:

         g_array[2] = g_count;
         TSC_WB(HIGH, LOW);           
         break;
   default:
         g_count = 0;
         break;
  }
}
 
void TSC_WB(int Level0, int Level1)    
{
  g_count = 0;
  g_flag ++;
  TSC_FilterColor(Level0, Level1);
  Timer1.setPeriod(1000000);           
}
 
void setup()
{           
  {

  TSC_Init();
  Serial.begin(115200);

  Timer1.initialize();           
  Timer1.attachInterrupt(TSC_Callback);  
  attachInterrupt(0, TSC_Count, RISING);  
 
  delay(4000);
 
  for(int i=0; i<3; i++)
    Serial.println(g_array[i]);
 
  g_SF[0] = 255.0/ g_array[0];    
  g_SF[1] = 255.0/ g_array[1];    
  g_SF[2] = 255.0/ g_array[2];   
  

  Serial.println(g_SF[0]);
  Serial.println(g_SF[1]);
  Serial.println(g_SF[2]);
  }
    


} 

void loop()
{   
   g_flag = 0;
   for(int i=0; i<3; i++)
    Serial.println(int(g_array[i] * g_SF[i]));

float RED = g_array[0] * g_SF[0];
float GREEN = g_array[1] * g_SF[1];
float  BLUE = g_array[2] * g_SF[2];



float VALUE1 = max(RED,GREEN);
float VALUE = max(BLUE,VALUE1);
float OCTAPER = VALUE/255;




Serial.println(OCTAPER);




if (RED >= BLUE && BLUE > GREEN) 
{
float BG = BLUE - GREEN;
float RG = RED - GREEN;
float RBG = 6 - (BG/RG);
float HUE = 60*(RBG);
float HUEPER0 = 1-(HUE/360);
float HUEPER = 1-HUEPER0;

Serial.println(HUEPER);

if (1 <= OCTAPER )
{
float OSC = 1;
Serial.println(OSC);
  }
else if (0.7 < OCTAPER && OCTAPER < 1)
{
float OSC = 784+784*HUEPER;
Serial.println(OSC);
  }
else if (0.6 < OCTAPER && OCTAPER < 0.7)
{
float OSC = 392+392*HUEPER;
Serial.println(OSC);
  }
else if (0.4 < OCTAPER && OCTAPER <= 0.6)
{
  float OSC = 196+196*HUEPER;
Serial.println(OSC);
  }
    else  if (0.1< OCTAPER && OCTAPER <= 0.4)
{
  float OSC = 98+98*HUEPER;
Serial.println(OSC);
  }
  else  if (0.081 < OCTAPER && OCTAPER <= 0.1)
{
  float OSC = 49+49*HUEPER;
Serial.println(OSC);
  }
  else  if (0.081 >= OCTAPER )
{
  float OSC = 0;
Serial.println(OSC);
  }

}





else if (BLUE > RED && RED >= GREEN) 
{
float RG = RED - GREEN;
float BG = BLUE - GREEN;
float BRG = 4 + (RG/BG);
float HUE = 60*(BRG);
float HUEPER0 = 1-(HUE/360);
float HUEPER = 1-HUEPER0;

Serial.println(HUEPER);

if (1 <= OCTAPER )
{
float OSC = 1;
Serial.println(OSC);
  }
else if (0.4 < OCTAPER && OCTAPER < 1)
{
float OSC = 784+784*HUEPER;
Serial.println(OSC);
  }
else if (0.25 < OCTAPER && OCTAPER < 0.4)
{
float OSC = 392+392*HUEPER;
Serial.println(OSC);
  }
else if (0.125 < OCTAPER && OCTAPER <= 0.25)
{
  float OSC = 196+196*HUEPER;
Serial.println(OSC);
  }
    else  if (0.1 < OCTAPER && OCTAPER <= 0.125)
{
  float OSC = 98+98*HUEPER;
Serial.println(OSC);
  }
  else  if (0.081 < OCTAPER && OCTAPER <= 0.1)
{
  float OSC = 49+49*HUEPER;
Serial.println(OSC);
  }
else  if (0.081 >= OCTAPER )
{
  float OSC = 0;
Serial.println(OSC);
  }

}





else if (BLUE > GREEN && GREEN > RED) 
{
float GR = GREEN - RED;
float BR = BLUE - RED;
float BGR = 4 - (GR/BR);
float HUE = 60*(BGR);
float HUEPER0 = 1-(HUE/360);
float HUEPER = 1-HUEPER0;

Serial.println(HUEPER);

if (1 <= OCTAPER )
{
float OSC = 1;
Serial.println(OSC);
  }
else if (0.60 < HUEPER && 0.5 < OCTAPER && OCTAPER < 1)
{
float OSC = 784+784*HUEPER;
Serial.println(OSC);
  }
else if (0.60 < HUEPER && 0.25 < OCTAPER && OCTAPER < 0.5)
{
float OSC = 392+392*HUEPER;
Serial.println(OSC);
  }
else if (0.60 < HUEPER && HUEPER <= 0.65 && 0.175 < OCTAPER && OCTAPER <= 0.25)
{
  float OSC = 196+196*HUEPER;
Serial.println(OSC);
  }
else  if (0.60 < HUEPER && HUEPER < 0.645 && 0.09 < OCTAPER && OCTAPER <= 0.175)
{
  float OSC = 98+98*HUEPER;
Serial.println(OSC);
  }
    else  if (0.6 < HUEPER && HUEPER < 0.645 && 0.081 < OCTAPER && OCTAPER <= 0.09)
{
  float OSC = 49+49*HUEPER;
Serial.println(OSC);
  }



else  if (0.645 < HUEPER && 0.1125 < OCTAPER && OCTAPER <= 0.125)
{
  float OSC = 98+98*HUEPER;
Serial.println(OSC);
  }
    else  if (0.645 <= HUEPER && 0.081 < OCTAPER && OCTAPER <= 0.1125)
{
  float OSC = 49+49*HUEPER;
Serial.println(OSC);
  }



  
 else if (HUEPER <= 0.60 && 0.5 < OCTAPER && OCTAPER < 1)
{
float OSC = 784+784*HUEPER;
Serial.println(OSC);
  }
 
else if (HUEPER <= 0.60 && 0.375 < OCTAPER && OCTAPER < 0.5)
{
float OSC = 392+392*HUEPER;
Serial.println(OSC);
  }
  else if (HUEPER <= 0.60 && 0.25 < OCTAPER && OCTAPER <= 0.375)
{
  float OSC = 196+196*HUEPER;
Serial.println(OSC);
  }
  else  if (HUEPER <= 0.60 && 0.125 < OCTAPER && OCTAPER <= 0.25)
{
  float OSC = 98+98*HUEPER;
Serial.println(OSC);
  }
  else  if (HUEPER <= 0.60 && 0.081 < OCTAPER && OCTAPER <= 0.125)
{
  float OSC = 49+49*HUEPER;
Serial.println(OSC);
  }


else  if (0.081 >= OCTAPER )
{
  float OSC = 0;
Serial.println(OSC);
  }

}





else if (GREEN >= BLUE && BLUE > RED) 
{
float BR = BLUE - RED;
float GR = GREEN - RED;
float GBR = 2 + (BR/ GR);
float HUE = 60*(GBR);
float HUEPER0 = 1-(HUE/360);
float HUEPER = 1-HUEPER0;

Serial.println(HUEPER);

if (1 <= OCTAPER )
{
float OSC = 1;
Serial.println(OSC);
  }
else if (0.9 < OCTAPER && OCTAPER < 1)
{
float OSC = 784+784*HUEPER;
Serial.println(OSC);
  }
else if (0.2 < OCTAPER && OCTAPER < 0.9)
{
float OSC = 392+392*HUEPER;
Serial.println(OSC);
  }



else if (0.1375 < OCTAPER && OCTAPER <= 0.2)
{
  float OSC = 196+196*HUEPER;
Serial.println(OSC);
  }
else  if (0.1125 < OCTAPER && OCTAPER <= 0.1375)
{
  float OSC = 98+98*HUEPER;
Serial.println(OSC);
  }
    else  if (0.085 < OCTAPER && OCTAPER <= 0.1125)
{
  float OSC = 49+49*HUEPER;
Serial.println(OSC);
  }
else  if (0.085 >= OCTAPER )
{
  float OSC = 0;
Serial.println(OSC);
  }

}





else if (GREEN > RED && RED >= BLUE) 
{
float RB = RED - BLUE;
float GB = GREEN - BLUE;
float GRB = 2 - (RB/GB);
float HUE = 60*(GRB);
float HUEPER0 = 1-(HUE/360);
float HUEPER = 1-HUEPER0;

Serial.println(HUEPER);

if (1 <= OCTAPER )
{
float OSC = 1;
Serial.println(OSC);
  }
else if (0.45 < OCTAPER && OCTAPER < 1)
{
float OSC = 784+784*HUEPER;
Serial.println(OSC);
  }
else if (0.25 < OCTAPER && OCTAPER < 0.45)
{
float OSC = 392+392*HUEPER;
Serial.println(OSC);
  }
else if (0.125 < OCTAPER && OCTAPER <= 0.25)
{
  float OSC = 196+196*HUEPER;
Serial.println(OSC);
  }
    else  if (0.081 < OCTAPER && OCTAPER <= 0.125)
{
  float OSC = 98+98*HUEPER;
Serial.println(OSC);
  }
else  if (0.081 >= OCTAPER )
{
  float OSC = 0;
Serial.println(OSC);
  }
  
}





else if (RED >= GREEN && GREEN >= BLUE && 95 > GREEN) 
{
float GB = GREEN - BLUE;
float RB = RED - BLUE;
float RGB = GB/RB;
float HUE = 60*(RGB);
float HUEPER0 = 1-(HUE/360);
float HUEPER = 1-HUEPER0;

Serial.println(HUEPER);


if (1 <= OCTAPER )
{
float OSC = 1;
Serial.println(OSC);
  }
else if (0.95 < OCTAPER && OCTAPER < 1)
{
float OSC = 1760+1760*HUEPER;
Serial.println(OSC);
  }
else if (0.8 < OCTAPER && OCTAPER < 0.95)
{
float OSC = 880+880*HUEPER;
Serial.println(OSC);
  }


else if (0.09 <= HUEPER && 0.5 < OCTAPER && OCTAPER <= 0.8)
{
  float OSC = 440+440*HUEPER;
Serial.println(OSC);
  }
    else  if (0.09 <= HUEPER && 0.19 < OCTAPER && OCTAPER <= 0.5)
{
  float OSC = 220+220*HUEPER;
Serial.println(OSC);
  }
  else  if (0.09 <= HUEPER && 0.09 < OCTAPER && OCTAPER <= 0.19)
{
  float OSC = 110+110*HUEPER;
Serial.println(OSC);
  }


else if (HUEPER < 0.09 && 0.5 < OCTAPER && OCTAPER <= 0.8)
{
  float OSC = 440+440*HUEPER;
Serial.println(OSC);
  }
else  if (HUEPER < 0.09 && 0.175 < OCTAPER && OCTAPER <= 0.5)
{
  float OSC = 220+220*HUEPER;
Serial.println(OSC);
  }
   else  if (HUEPER < 0.09 && 0.09 < OCTAPER && OCTAPER <= 0.175)
{
  float OSC = 110+110*HUEPER;
Serial.println(OSC);
  }


  
else  if (0.081 < OCTAPER && OCTAPER <= 0.09 )
{
  float OSC = 55+55*HUEPER;
Serial.println(OSC);
  }
else  if (0.081 >= OCTAPER )
{
  float OSC = 0;
Serial.println(OSC);
  }

}





else if (RED >= GREEN && GREEN >= BLUE && GREEN >= 95) 
{
float GB = GREEN - BLUE;
float RB = RED - BLUE;
float RGB = GB/RB;
float HUE = 60*(RGB);
float HUEPER0 = 1-(HUE/360);
float HUEPER = 1-HUEPER0;

Serial.println(HUEPER);

if (1 <= OCTAPER )
{
float OSC = 1;
Serial.println(OSC);
  }


  
else if (0.089 <= HUEPER && 0.94 <= OCTAPER && OCTAPER < 1)
{
float OSC = 1760+1760*HUEPER;
Serial.println(OSC);
  }

else if (0.089 <= HUEPER && 0.9 <= OCTAPER && OCTAPER < 0.94)
{
float OSC = 880+880*HUEPER;
Serial.println(OSC);
  }
  
else if (0.085 <= HUEPER && 0.775 <= OCTAPER && OCTAPER < 0.9 )
{
float OSC = 440+440*HUEPER;
Serial.println(OSC);
  }
else  if (0.085 <= HUEPER && 0.19 < OCTAPER && OCTAPER <= 0.25)
{
  float OSC = 220+220*HUEPER;
Serial.println(OSC);
  }
  else  if (0.085 <= HUEPER && 0.081 < OCTAPER && OCTAPER <= 0.19)
{
  float OSC = 110+110*HUEPER;
Serial.println(OSC);
  }
else  if (0.085 <= HUEPER && 0.081 >= OCTAPER )
{
  float OSC = 0;
Serial.println(OSC);
  }


  
  
  else if (HUEPER < 0.089 && 0.9 <= OCTAPER && OCTAPER < 1 )
{
float OSC = 1760+1760*HUEPER;
Serial.println(OSC);
  }
else if (HUEPER < 0.085 && 0.775 <= OCTAPER && OCTAPER < 0.9 )
{
float OSC = 880+880*HUEPER;
Serial.println(OSC);
  }



  else if (0.0627 < HUEPER && HUEPER < 0.089 && 0.25 < OCTAPER && OCTAPER < 0.5)
{
float OSC = 440+440*HUEPER;
Serial.println(OSC);
  }
else if (HUEPER <= 0.0627 && 0.25 < OCTAPER && OCTAPER <= 0.5)
{
  float OSC = 440+440*HUEPER;
Serial.println(OSC);
  }  

  
else  if (HUEPER < 0.085 && 0.19 < OCTAPER && OCTAPER <= 0.25)
{
  float OSC = 220+220*HUEPER;
Serial.println(OSC);
  }
  else  if (HUEPER < 0.085 && 0.081 < OCTAPER && OCTAPER <= 0.19)
{
  float OSC = 110+110*HUEPER;
Serial.println(OSC);
  }
else  if (HUEPER < 0.085 && 0.081 >= OCTAPER )
{
  float OSC = 0;
Serial.println(OSC);
  }

}



   delay(4000);
 
}


