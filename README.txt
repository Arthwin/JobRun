Daniel Olarte y Daniel Cossio

jobRun es un programa, que dado una descripcion YAML 
ejecuta otro programa con ciertas opciones.

El archivo de entrada debe tener el formato:

Job :
 Name : <Job Name>
 Exec : <Executable>
 Args : [<Arguments>]
 Input : <Input>
 Output : <Output>
 Error : <Error>

Un ejemplo: 

Job:  
    Name :    test-job 
    Exec :    echo 
    Args :    [-n,this is a test] 
    Input :   stdin 
    Output :  stdout 
    Error :   stderr

Para compilar el .cpp:
g++ -I/usr/local/include -L/usr/local/lib -lyaml-cpp -o jobRun jobRun.cpp

Para correr el programa:
./jobRun desc.yaml

NOTA: si la entrada/salida no es estandar, se requiere que se de como parte de la descripcionm los permisos nesesarios.
