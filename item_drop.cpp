//the answer to  question: how can it be 
//realized calcuations for item drop in games
//where after win monsters u have some items
//the main idea that only one item can be 
//dropped at time and after number of target 
//iterration the dropped prcentege should be
//closer to started rate. and every roll drop 
//rate of one item increased exponentionally or linear


#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <cstdlib>

//#include <random>
#include <ctime>
#include <cmath>

#define TESTT

//item data struct
struct smartItem
{  smartItem(std::string _name,
	             float _dropRate):
	        name(_name),
	        dropRate(_dropRate),
	        currentDropRate(_dropRate),
	        currentDropStep(1){};
	        
	std::string name;
	float dropRate,
	    currentDropRate;
	int currentDropStep;
 };

 //ony one item asn be dropped at time.if drop happen it added to drop sequence.
class smartDrop
{
public:
//s("itemName dropChance(1-100), ...", target 100);
	
//smartDrop(" sword 54, mace 31, mail 7",10);
smartDrop(std::string sItems,
	      int iTarget,
	      std::string sGrowingType)
{//parse string to vector-item name drop chance
Target=iTarget;
GrowingType=sGrowingType;
		
int iCurrentPos=0;
float iRate;
std::string sName;
		
for(auto i=0; i<sItems.size();i++)  
if(sItems[i]!='/0'){
	
if(sItems[i]==' '){
sName=sItems.substr(iCurrentPos+1,i-iCurrentPos-1);
iCurrentPos=i;};

if(sItems[i]==','){
iRate=float(std::stoi(sItems.substr(iCurrentPos,
	                  i-iCurrentPos)));
iCurrentPos=i;
Items.push_back(smartItem(sName,iRate));
/////////////////////////////////////////////
statCounter.push_back(0);	                 
	                   };//','

		};//end for()

#ifdef TEST
		
	std::cout<<"ctor::target = "<<Target<<std::endl;
	for(auto i:Items)
	std::cout<<i.name
	         <<" "
	         <<i.dropRate
	         <<" ("
	         <<i.currentDropRate
	         <<") - step "
	         <<i.currentDropStep
	         <<std::endl;
#endif		
		
};//end ctor - parser
				
//generating next step of rolling item and add it to drop sequence.
void roll()
{
int iRand;
int item=0;
static int iRandSeed;
	
for(auto& i:Items)
{

std::srand(iRandSeed++);//seed
iRand=(std::rand()%100);

#ifdef TEST 	
std::cout<<"iRand = "
	     <<iRand
	     <<" "
	     <<i.name
	     <<" "
	     <<i.dropRate
	     <<" ("
	     <<i.currentDropRate
	     <<")-step "
	     <<i.currentDropStep
	     <<"|"
	        // <<std::endl
	         ;
#endif

if(iRand<i.currentDropRate){
	if(std::find(dropSequence.begin(),
	             dropSequence.end(),
	             item)==dropSequence.end())
	
 	dropSequence.emplace(dropSequence.begin(),                    item);
	}
	
//std::cout<<"#else#";
//calculate new droprate for current item
i.currentDropStep+=1;	  
if(this->GrowingType=="exponential")		
   {
   	
float A=(100-i.dropRate);
float B=pow(2,(this->Target));
float C=pow(2,(i.currentDropStep));

#ifdef TEST 	
std::cout<<" exp= "
	     <<A
	     <<" / "
	     <<B
         <<" * "
	     <<C
	     <<std::endl;
	     
#endif      
   	
i.currentDropRate+=(A/B*C);             
    }//exponential type block
else if(this->GrowingType=="linear")		
   {
   	
float A=(100-i.dropRate);
float B=(this->Target);

#ifdef TEST 	
std::cout<<" lin= "
	     <<A
	     <<" / "
	     <<B
	     <<std::endl;     
#endif   
   	
i.currentDropRate+=(A/B);             
    }//linear type block
   
  ++item;

 }//for(auto i:Items)
#ifdef TEST 	

std::cout<<" dSeq =[ ";

for(int i:dropSequence)
std::cout<<Items[i].name<<" ";

std::cout<<"]"
 	     <<std::endl;
#endif
 
	};//roll()
		
//checking drop sequence. return oldest item or empty
std::string drop()
	{
if(dropSequence.empty())return "empty";
		else
		//if something added in dropsequence return string with name and reset the drop rate and steps
   {
int itemId=*(dropSequence.end()-1);
std::string dropName=Items[itemId].name;
Items[itemId].currentDropRate=
	                	Items[itemId].dropRate;
Items[itemId].currentDropStep=1;
dropSequence.pop_back();
	                	
statCounter[itemId]=statCounter[itemId]+1;
	                	
return 	dropName;
		}	//else		
		}
		
//statistic of dropping items
//item_name target_drop_rate(real_drop_rate)
std::string stat(int iterNum)
{
	std::string str("");
	int iStat=0;
	std::cout<<"item_name target_drop_rate(real_drop_rate)"
		     <<std::endl;
	for(auto i:Items)
	{
		
#ifdef TEST
for(int i:statCounter)
		std::cout<<i<<" ";
std::cout<<std::endl;
		
#endif
  std::cout<<i.name
	       <<" "
	       <<Items[iStat].dropRate
	       <<" ("
	       <<std::to_string(
		   float(1.0f
		        /float(iterNum)
		        *float(statCounter[iStat++])
		        *100.0f
		        )
		                )
	    <<")"		
	    <<std::endl;
		;	
	}
	
return str;
}
		
private:
   std::vector<smartItem> Items;//Items can be dropped on the boss
   int Target,//target try when drop 100% must happen
	   Current;//current number of try
   std::string GrowingType;//substraction distribution type
	std::vector<int> dropSequence;//sequence of items can be dropped
	std::vector<int> statCounter;//stats of dropping items
	};

int main()
{
auto start=std::chrono::system_clock::now();
////////////////////////////////////////////////
	
//	for(int i=0;i<1000;i++)
//	{std::cout<<(rand()%256<128);}

int target=100,
    dropCount=115;
smartDrop Boss1(" sword 14, mace 3, mail 7, flask 65, gold 50,",target,"linear");

for(int i=1;i<=dropCount;i++)
{
Boss1.roll();
std::cout<<"--->"
	     <<Boss1.drop()
	     <<"<---"
	     <<std::endl
	     ;
}

Boss1.stat(dropCount);
////////////////////////////////////////////////

auto end=std::chrono::system_clock::now();
auto dif=std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
std::cout<<std::endl<<dif<< " ms";
}
