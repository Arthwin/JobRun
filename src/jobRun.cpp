#include "yaml-cpp/yaml.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>

/* La Estructura

- Job :
	Name : <Job Name>		// "test-job"
	Exec : <Executable>		// "echo"
	Args : [<Arguments>]	// ["-n","this is a test"]
	Input : <Input>			// "stdin"
	Output : <Output>		// "stdout"
	Error : <Error>			// "stderr"
*/


// Tipos de datos

struct Job {
 std::string Name;
 std::string Exec;
 std::vector <std::string> Args;
 std::string Input;
 std::string Output;
 std::string Error;
};


// Operadores de extraccion
void operator >> (const YAML::Node& node, Job& job) 
{
 node["Name"] >> job.Name;
 node["Exec"] >> job.Exec;
 const YAML::Node& args = node["Args"];
 for(unsigned i=0;i<args.size();i++) 
 {
  std::string str;
  args[i] >> str;
  job.Args.push_back(str);
 }
 node["Input"] >> job.Input;
 node["Output"] >> job.Output;
 node["Error"] >> job.Error;
}

int main()
{
 //Leemos el Archivo
 std::ifstream fin("desc.yaml");
 YAML::Parser parser(fin);
 YAML::Node doc;
 parser.GetNextDocument(doc);
 //Suponemos que solo hay 1 Job, si no falta un for
 Job job;
 doc["Job"] >> job;
 std::cout << "## Running " << job.Name << " ##\n";		//Suponemos que el mensaje de entrada y salida son por la salida estandar
 try
 {
  //Tratamos de Correr el Programa
  //Entradas
  std::string prgrm = job.Exec;
  if(job.Input != "stdin")				//Entrada de Archivo
  {   
   std::string inp;
   std::ifstream input; 
   char * charstring = new char[job.Input.length()+1];
   std::strcpy (charstring,job.Input.c_str());
   input.open(charstring); 
   input >> inp;
   input.close();
   prgrm += inp;
  }
  else								//Entrada Estandar
  {
   for(unsigned i=0;i<job.Args.size();i++)
   {
    prgrm += " " + job.Args[i];
   }
  }
  //Salidas
  char * charstring = new char[prgrm.length()+1];
  std::strcpy (charstring,prgrm.c_str());
  if(job.Output == "stdout")
  {
    system(charstring);		//Salida Estandar
  }
  else
  {
   char * charstring = new char[job.Output.length()+1];
   std::strcpy (charstring,job.Output.c_str());
   std::ofstream output;	
   output.open (charstring);		//Salida a Archivo
   output << system(charstring);
   output.close();
  }
  std::cout << "\n## " << job.Name << " finished Successful ##\n";		//Suponemos que el mensaje de entrada y salida son por la salida estandar
 }
 catch (int e)						//Fallo el Programa
 {
  std::cout << "\n## " << job.Name << " finished Unsuccessful(Err: " << job.Error << e << ") ##\n";		//Suponemos que el mensaje de entrada y salida son por la salida estandar
 }
 return 0;
}
