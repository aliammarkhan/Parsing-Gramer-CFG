#include<iostream>
#include<stdio.h>
#include<fstream>
#include<string>
#include<string.h>
using namespace std;



bool dualpd = false;     //to check if a word is both pronoun and determiner
bool dualnv = false;     //to check if a word is both verb and noun
bool isVP = false;
int dualindexpd = -1;    //indexes of the dual words
int dualindexnv = -1;
string output[100];      //output string
int o_index = 0;

template <typename T>
class DSA{    // Dynamic Safe Array
	private :

	int size;

	public :
		T *Data;
		DSA(){
			size = 0;
			Data = 0;

		}
		DSA(int s){
			size = s;
				Data = new T[size];

		}
		DSA(const DSA&rhs){
				size = rhs.size;
				Data = new T[size];

			for(int i =0 ; i<size;i++){
				memcpy(Data,rhs.Data,sizeof(T)*size);
			}
		}


		DSA& operator=(const DSA &rhs){
			if(this != &rhs){

			size = rhs.size;
			Data = new int[size];
			for(int i =0 ; i<size;i++){
				memcpy(Data,rhs.Data,sizeof(T)*size);
			}

		}
		else return *this;

		}






    ~DSA(){

			if(Data!=0){
			delete[] Data;
			}
		}
};
	template <typename T>
	class stack{
		private:

		int size;
		int top;
		public:
		DSA<T> *Data;
		stack(){
			Data= new DSA<T>();
			Data=0;
			top=0;
			size=0;
		}
		stack(int n){
			size=n;
			Data= new DSA<T>(size);
			top=-1;
		}

		void push(T element){

			if(top < size-1){
			top++;
			Data->Data[top]=element;
			}else{
				cout<<"Stack is full"<<endl;
			}
		}
		T pop(){

			if(top>-1){
				top--;
				return Data->Data[top+1];
			}else{
				cout<<"Stack is Empty"<<endl;
				;
			}

		}


	int  gettop(){
		return top+1;
	}
	void Peek(){

		cout<<Data->Data[top];


	}
	bool isempty()
	 {
	   if(Data->Data[top]=="$")
	    return true;
	 }

};

 bool check_noun(string s[],int index , int j)
{
    if(index>j || dualindexnv==index)
   return false;

string fromfile;

ifstream read("nouns.txt");

   while(!read.eof()){

          read >> fromfile;
         if(s[index] == fromfile)
          return true;
  }
  return false;
}

 void Output(string pushed,string rep,string repwith,string adjust) //to print the output string
 {

   int i =0;


   if(pushed != "0"){    // to push non terminals in the array
  output[o_index] = pushed;
  o_index ++;
  }

  if(rep!="0"&&repwith!="0"){    //replaces a non terminal
  while(output[i]!="\0")
  {


    if(output[i]==rep)
    {

     output[i]=repwith;
     break;
    }
    i++;
}
}


   if(adjust!="0"&&o_index!=0){   //adjust a non terminal a/c to its position

    if(output[i+1] == "\0"){



	  output[o_index] = adjust;
      o_index ++;

	}
	else{


	output[o_index]= output[o_index-1];
    output[o_index-1] = adjust;
    o_index++;
}


   }



i = 0;
   while(output[i]!="\0")
  {
      if(output[i]=="0")
      i++;

      cout<<output[i]<<" ";
      i++;

  }
   cout<<endl;
}

  void check_dualnv(string s , int index)   //checks if a word is both noun and verb
  {

     string fromfile;
      ifstream obj("verbs.txt");
     while(!obj.eof()) {

      obj>>fromfile;

      if(fromfile==s)
      {

          dualindexnv = index;
          dualnv = true;
          break;


      }

    }
    obj.close();

  }
   void check_dualpd(string s , int index) //checks if a word is both pronoun and Determiner
  {

      string fromfile;
      ifstream obj("determiners.txt");
     while(!obj.eof()) {

      obj>>fromfile;

      if(fromfile==s)
      {

          dualindexpd = index;
          dualpd = true;
          break;


      }

    }
    obj.close();

  }

int NP (string s[] ,string pushed,int index,int j)
{
   stack <string>obj1(100);
   if(pushed!="$"){
   obj1.push("$");  //starting symbol , shows the stack is empty
   obj1.push(pushed);
   }
   else
   obj1.push(pushed);

   bool found = false;
  string fromfile;
  string S="";

  if(pushed == "$")
  obj1.push("pronouns"); //first pushes the pronoun onto the stack


   while(!obj1.isempty())
   {

      if(index > j&& isVP==true) //If string has be consumed then the structure will be valid
      {
        cout<<"\nStructure is valid !!\n";
        exit(0);


      }

     S = obj1.pop();  // pops non terminals from stack

     if(S == "pronouns")
     {

      S =S+".txt";
      ifstream read(S);

      while(!read.eof()) {

      read>>fromfile;
      if(fromfile==s[index]&&dualindexpd!=index)      //check if the each terminal in file corresponding to non terminal popped
      {                                               //dualindexpd is the index of a word tht belong to two different parts of speech(pronoun and determiner)
         found = true;
         check_dualpd(fromfile,index);        //check for duality
       //  cout<<"\nNP -----> pronouns\npronouns-----> "<<s[index]<<endl;
           Output("0","NP","Pro","0");  //manages the output string array
          Output("0","Pro",s[index],"0");
         index++;
         break;

      }

    }
      read.close();

         if(found == false)  //If the current non terminal is not present,push the next
         {
            obj1.push("propernouns");

         }

      }
    else if(S == "propernouns")  //check if the each terminal in file corresponding to non terminal popped
    {

      S =S+".txt";
      ifstream read(S);
      while(!read.eof()) {

      read>>fromfile;
      if(fromfile==s[index])
      {
         found = true;
         //cout<<"\nNP -----> Propernouns\nPropernouns-----> "<<s[index]<<endl;
         Output("0","NP","Prop","0");
         Output("0","Prop",s[index],"0");
         index++;
        break;

      }

    }
      read.close();

         if(found == false)  //If the current non terminal is not present,push the next
         {
            obj1.push("determiners");

         }




    }

    else if(S == "determiners")
    {

        S =S+".txt";
      ifstream read(S);
      while(!read.eof()) {

      read>>fromfile;
      if(fromfile==s[index])
      {

         found = true;
         //cout<<"\nNP -----> Determiners Nominals\nDeterminers-----> "<<s[index]<<endl;
         Output("0","NP","Det","Nom");
         Output("0","Det",s[index],"0");
         index++;
         break;

      }

    }
      read.close();

         if(found == true) //If determiner is present then and only push Nominal
         {
            obj1.push("Nominal");

         }



    }

    else if(S == "Nominal") //checks for Nominals
    {

        S ="nouns.txt";
      ifstream read(S);


      while(!read.eof()) {

      read>>fromfile;
      if(fromfile==s[index]&&dualindexnv!=index)   //dualindexnv is the index of a word tht belong to two different parts of speech(noun and verbs)
      {
         bool x = check_noun(s,index+1,j);
         found = true;

        if(x){
        Output("0","Nom","noun","Nom");
        Output("0","noun",s[index],"0");
       }
       else{
       Output("0","Nom","noun","0");
       Output("0","noun",s[index],"0");
       found = false;
       }
       check_dualnv(fromfile,index); //check for duality

         index++;
         break;

      }

    }
      read.close();
    if(found == true )
     obj1.push("Nominal");





    }

    found = false;
}
    return index;

}

int VP(string s[],int index ,int j) //checks all VP productions
 {

    if(isVP)
    return index;


    stack <string>obj1(100);
   obj1.push("$");
   bool found = false;
  string fromfile;
  string S;

  obj1.push("verbs");


   while(!obj1.isempty())
   {

      if(index > j&&isVP==true)   //if string consumed then structure is valid
      {
        cout<<"\nStructure is valid !!\n";
        exit(0);


      }

     S = obj1.pop();

     if(S == "verbs")  //first pushes Verbs
     {


      S =S+".txt";
      ifstream read(S);
      while(!read.eof()) {

      read>>fromfile;
      if(fromfile==s[index])
      {   isVP = true;
         found = true;
        // cout<<"\nVP -----> verbs\nverbs-----> "<<s[index]<<endl;
         Output("0","VP","verbs","0");
         Output("0","verbs",s[index],"0");
         index++;

      }

    }
      read.close();

         if(found == true)  //if verb present then check for all other possible VP productions
         {

           obj1.push("VerbNPPP");
           obj1.push("VerbNP");
           obj1.push("VerbPP");

         }

      }

      else if (S=="VerbPP")  // for VP ---> verb PP prodctions
      {

          S ="prepositions.txt";
      ifstream read(S);
      while(!read.eof()) {

      read>>fromfile;
      if(fromfile==s[index])
      {
         isVP = true;
       //  cout<<"\nVP -----> Verb PP\nVP-----> "<<s[index-1]<<" PP"<<endl;
        // cout<<"\nPP ---->Preposition NP"<<"\nPreposition ---->"<<s[index]<<endl;
        Output("PP","0","0","0");
        Output("0","PP","Prepositions","0");
        Output("0","Prepositions",s[index],"0");

         index++;
          Output("NP","0","0","0");
          int tmpindex = NP(s,"$",index,j);
        if(tmpindex == index)   // if NP does not incerement the index then NP is not present and structure will be in valid
           {
               cout<<"\n\nStructure is in valid !! \n\n";
                exit(0);
          }
          index = tmpindex;
         found = true;

      }

    }
      read.close();



    }
   else if (S == "VerbNP")   // checks for VP ---> verb NP production
   {
    //cout<<"VP ----> NP\n";
    Output("NP","0","0","0");
    index = NP(s,"$",index,j);

   }

   else if (S =="VerbNPPP")   //checks for vp ---> Verb NP PP productions
   {
    // index = NP(s,index,j);
     obj1.push("VerbPP");

   }

 }
  return index;

}
void  parse(string s[],int j)
 {
    string S;
    int index = 0;

   stack<string>obj(100);
   obj.push("$");  //pushes the empty identifier
   obj.push("S"); // first pushes S
   Output("S","0","0","0");

 while(!obj.isempty())
 {
    S = obj.pop();
   if(index>j&&isVP==true)  // if string consumed then structure is valid
   {
      cout<<"\n\nStructure is valid !! \n\n";
      exit(0);

   }

    if(S == "S")   // is S found at top push the other non terminals VP and NP
    {

      obj.push("VP");
      obj.push("NP");
      Output("0","S","NP","0");
      Output("VP","0","0","0");
     // cout<<"\nS---->NP | VP\n";

    }

    else if(S == "NP")
    {

      index = NP(s,"$",index,j);  //checks for all  NP productions
      if(index == 0)
      {
         cout<<"\n\nStructure is invalid\n\n";
         exit(0);
      }

    }

     else if(S == "VP")
    {

      index = VP(s,index,j);  //checks for all VP productions


    }

    if(index>j&&isVP==true) //string consumed then true
   {
      cout<<"\n\nStructure is valid !! \n\n";
      exit(0);

   }

 }
 if(dualnv == true) //if string is not consumed and duality exist so check for the other speech
 {
  system("cls");
 	 int i = 0;

  // index=VP(s,dualindexnv,j);
     while(output[i]!="\0")
     {
     	output[i] = "\0";
     	i++;
     }
     //Resetting all conditions to initial
	o_index = 0;
    Output("S","0","0","0");
    Output("0","S","NP","0");
    Output("VP","0","0","0");

     isVP=false;
     obj.push("VP");
	 index = NP(s,"$",0,j);
	 index = VP(s,index,j);
 }

  if(dualpd == true)
   {

      system("cls");
 	 int i = 0;

  // index=VP(s,dualindexnv,j);
   //Resetting all conditions to initial
     while(output[i]!="\0")
     {
     	output[i] = "\0";
     	i++;
     }
	o_index = 0;
    Output("S","0","0","0");
    Output("0","S","NP","0");
    Output("VP","0","0","0");

     isVP=false;
     obj.push("VP");
	 index = NP(s,"$",0,j);
	 index = VP(s,index,j);

   }


  if(index>j&&isVP==true)
   {
      cout<<"\n\nStructure is valid !! \n\n";
      exit(0);

   }
   else
cout<<"\n\nStructure is invalid\n\n"<<index;



 }



int main(){

  string s1,s[100];
  int i = 0,j=0;

cout<<"Enter your sentence:";
 getline(cin,s1);
while(i<s1.size())   //converts the entered the string to an array of strings
                     //each index will hold a single word
{
  if(s1[i]!=' ')
  s[j]+=s1[i];
  else
  j++;
  i++;

}



parse(s,j);

return 0;



}

