
#include <stdio.h>
#include <webots/robot.h>
#include <webots/motor.h>
#include <webots/distance_sensor.h>
#include <webots/led.h>
#include <webots/supervisor.h>

#define TIME_STEP 256
#define QtddSensoresProx 8
#define QtddLeds 10

WbDeviceTag Leds[QtddLeds];
void acionarLed(int qtdLeds, int valor);

int main(int argc, char **argv) {
  
  int i=0;
  char texto[256];
  double LeituraSensorProx[QtddSensoresProx];
  double AceleradorDireito=1.0, AceleradorEsquerdo=1.0;
  //Parametros caixa.
  bool isCaixaMovel = false;
  int caixasAtingidas = 1;
  bool caixaChecada = false;
  
for(i=0;i<256;i++) texto[i]=0;
  
  wb_robot_init();
  
  //configurei MOTORES
  WbDeviceTag MotorEsquerdo, MotorDireito;
  WbDeviceTag accelerometer = wb_robot_get_device("accelerometer");
  //Parametros Gyro
  WbDeviceTag gyro = wb_robot_get_device("gyro");
  wb_accelerometer_enable(accelerometer, TIME_STEP);
  wb_gyro_enable(gyro, TIME_STEP);
  const double *b = wb_gyro_get_values(gyro);
  
  MotorEsquerdo = wb_robot_get_device("left wheel motor");
  MotorDireito = wb_robot_get_device("right wheel motor");

  
  WbNodeRef robot_node = wb_supervisor_node_get_from_def("ePuck"); //captura o supervisor
  WbNodeRef caixa_node1 = wb_supervisor_node_get_from_def("caixaMovel"); //captura a caixa movel

  WbFieldRef trans_field = wb_supervisor_node_get_field(robot_node, "translation"); //identifica o campo de posição
  WbFieldRef trans_field_box1 = wb_supervisor_node_get_field(caixa_node1, "translation");
  const double *posicaoRobo; //variáel que vai receber a posição do robo
  const double *posicaoBox1;  
  
  wb_motor_set_position(MotorEsquerdo, INFINITY);
  wb_motor_set_position(MotorDireito, INFINITY);
  
  wb_motor_set_velocity(MotorEsquerdo,0);
  wb_motor_set_velocity(MotorDireito,0);
  
  
   //configurei Sensores de Proximidade
   WbDeviceTag SensorProx[QtddSensoresProx];
   
   SensorProx[0] = wb_robot_get_device("ps0");
   SensorProx[1] = wb_robot_get_device("ps1");
   SensorProx[2] = wb_robot_get_device("ps2");
   SensorProx[3] = wb_robot_get_device("ps3");
   SensorProx[4] = wb_robot_get_device("ps4");
   SensorProx[5] = wb_robot_get_device("ps5");
   SensorProx[6] = wb_robot_get_device("ps6");
   SensorProx[7] = wb_robot_get_device("ps7");
   
   wb_distance_sensor_enable(SensorProx[0],TIME_STEP);
   wb_distance_sensor_enable(SensorProx[1],TIME_STEP);
   wb_distance_sensor_enable(SensorProx[2],TIME_STEP);
   wb_distance_sensor_enable(SensorProx[3],TIME_STEP);
   wb_distance_sensor_enable(SensorProx[4],TIME_STEP);
   wb_distance_sensor_enable(SensorProx[5],TIME_STEP);
   wb_distance_sensor_enable(SensorProx[6],TIME_STEP);
   wb_distance_sensor_enable(SensorProx[7],TIME_STEP);

    //config leds
    Leds[0] = wb_robot_get_device("led0");
    Leds[1] = wb_robot_get_device("led1");
    Leds[2] = wb_robot_get_device("led2");    
    Leds[3] = wb_robot_get_device("led3");
    Leds[4] = wb_robot_get_device("led4");    
    Leds[5] = wb_robot_get_device("led5");
    Leds[6] = wb_robot_get_device("led6");
    Leds[7] = wb_robot_get_device("led7");    
    Leds[8] = wb_robot_get_device("led8");
    Leds[9] = wb_robot_get_device("led9");     
    wb_led_set(Leds[0],-1);
  
  while (wb_robot_step(TIME_STEP) != -1) {
    for(i=0;i<256;i++) texto[i]=0;

    for(i=0;i<QtddSensoresProx;i++){
       LeituraSensorProx[i]= wb_distance_sensor_get_value(SensorProx[i])-60;
    }
    printf("%s\n",texto);
    wb_led_set(Leds[0], wb_led_get(Leds[0])*-1);
    
    float media = (b[0] + b[1])/2;
    //Verifico através do gyro a velocidade das rodas.
        for(i = 0; i < caixasAtingidas; i++)
          {
            acionarLed(caixasAtingidas, 1);
          }
    
     posicaoRobo = wb_supervisor_field_get_sf_vec3f(trans_field);
     posicaoBox1 = wb_supervisor_field_get_sf_vec3f(trans_field_box1);
     float areaBox1 = posicaoBox1[0] * posicaoBox1[1];
     float distanciaCaixaX = posicaoRobo[0] - posicaoBox1[0];
     float distanciaCaixaY = posicaoRobo[1] - posicaoBox1[1];
   
    if((distanciaCaixaX>-0.110797 && distanciaCaixaX< -0.086810)  && distanciaCaixaY <0.00527)
    {
      printf("\nisso: %2f", distanciaCaixaX);
      isCaixaMovel = true;
      if(isCaixaMovel){
        for(i = 0; i < 3; i++)
        {
            acionarLed(10, 1);
            wb_robot_step(100);
            acionarLed(10, 0);
            wb_robot_step(100);
        }   
          
        } 
        
        isCaixaMovel= false;
        if(caixaChecada==false){
        caixasAtingidas++;
        for(i = 0; i < caixasAtingidas; i++)
          {
            acionarLed(caixasAtingidas, 1);
          }
          caixaChecada = true;
          }
          
          printf("Quantidade de caixas colididas: %d;\n", caixasAtingidas);
          
    } 
    
    if(media >=-0.059 && media<=0.058){
    printf("chora paixao");
    
    //Logica dos sensora
    //ps0(frontal direito)
    if (LeituraSensorProx[0] > 250)
      {
        printf("Sensor 0 ativado!");
        AceleradorDireito = 1;
        AceleradorEsquerdo = -0.9;
      }
    //ps1(dianteiro direito)
    else if (LeituraSensorProx[1] > 100)
      {
        printf("Sensor 1 ativado!");
        AceleradorDireito = 1;
        AceleradorEsquerdo = -0.2;
      }    
    //ps2(meio direito)
    else if (LeituraSensorProx[2] > 100)
      {
        printf("Sensor 2 ativado!");
        AceleradorDireito = 1;
        AceleradorEsquerdo = -0.5;
      }        
    //ps3(traseiro direito)
     else if (LeituraSensorProx[3] > 100)
      {
        printf("Sensor 3 ativado!");
        AceleradorDireito = 1;
        AceleradorEsquerdo = -0.9;
      }     
    //ps4(traseiro esquerdo)
    if (LeituraSensorProx[4] > 100)
      {
        printf("Sensor 4 ativado!");
        AceleradorDireito = -0.9;
        AceleradorEsquerdo = 1;
      }    
    //ps5(meio esquerdo)
    else if (LeituraSensorProx[5] > 100)
      {
        printf("Sensor 5 ativado!");
        AceleradorDireito = -0.5;
        AceleradorEsquerdo = 1;
      }       
    //ps6(dianteiro esquerdo)
    else if (LeituraSensorProx[6] > 100)
      {
        printf("Sensor 6 ativado!");
        AceleradorDireito = -0.2;
        AceleradorEsquerdo = 1;
      }       
    //ps7(frontal esquerdo)
    else if (LeituraSensorProx[7] > 100)
      {
        printf("Sensor 7 ativado!");
        AceleradorDireito = -0.1;
        AceleradorEsquerdo = 1;
      }    
          wb_motor_set_velocity(MotorEsquerdo,6.28*AceleradorEsquerdo);
          wb_motor_set_velocity(MotorDireito, 6.28*AceleradorDireito);
    }else{
      printf("sai do for vei");
        AceleradorDireito = 1;
        AceleradorEsquerdo = 1;
          wb_motor_set_velocity(MotorEsquerdo,1.28*AceleradorEsquerdo);
          wb_motor_set_velocity(MotorDireito, 1.28*AceleradorDireito);
    }
 
   
      wb_motor_set_velocity(MotorEsquerdo,6.28*AceleradorEsquerdo);
      wb_motor_set_velocity(MotorDireito, 6.28*AceleradorDireito);


  };

  wb_robot_cleanup();

  return 0;
}

void acionarLed(int qtdLeds, int valor)
{
    for(int i = 0; i < qtdLeds; i++){
       wb_led_set(Leds[i], valor);
    }
}
