//Written by A.N Sarkar for COMP6771 at UNSW
//z5061286
//Assignment 1
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <cmath>

//numStack is used to store the numbers on the stack
std::stack<std::string> numStack; 
//repQueue is the queue of moves to repeat
std::queue<std::string> repQueue;
//loopNum is the number of loops to make for a repeat sequence
int loopNum;
//this flag will tell parseInput whether or not to store moves in the repeatQueue
bool storeRepeatFlag = false;

void parseInput(std::string);
void sub();
void add();
void mult();
void div();
void sqrt();
void initRepeat();
void executeRepeatSequence();
void reverse();
void pushNum(std::string);

int main(int argc, char* argv[]) {
	// setup the print out format for the precision required.
	std::cout.setf(std::ios::fixed,std::ios::floatfield);
	std::cout.precision(3);

	// open the file for reading
	std::ifstream in;
	in.open(argv[1]); 

	// string to be read into
	std::string s;

	// read the file while we have input.
	while (in >> s) {
		parseInput(s);
	}
	in.close();
}

void parseInput(const std::string in){
	if(in.find("endrepeat") != std::string::npos){
		//if endrepeat is called then we run the repeat sequence, and set teh falg back to false
		storeRepeatFlag = false;
		executeRepeatSequence();
		return;
	}
	if(storeRepeatFlag == true){
		//while the endrepeat token has not been called we continue to store actions in queue
		repQueue.push(in);
		return;
	}
	if(isdigit(in[0]) || isdigit(in[1])){
		//if the input is an integer/double we add onto stack as string
		pushNum(in);
	} else {
		//otherwise we check what command it is and execute the corresponding function
		if(in.find("sub") != std::string::npos){
			sub();
		} else if (in.find("add") != std::string::npos){
			add();
		} else if (in.find("mult") != std::string::npos){
			mult();
		} else if (in.find("div") != std::string::npos){
			div();
		} else if (in.find("sqrt") != std::string::npos){
			sqrt();
		} else if (in.find("pop") != std::string::npos){
			numStack.pop();
		} else if (in.find("reverse") != std::string::npos){
			reverse();
		} else if (in.compare("repeat") == 0){
			initRepeat();
		}
	}
}

void pushNum(std::string strNum){
	//this will format doubles properly before adding to string stack
	//i.e append zero's to match 3 precision or truncate
	if(strNum.find(".") != std::string::npos){
		if(strNum.substr(strNum.find("."), strNum.length()).length() > 3){
			//truncate
			strNum = strNum.substr(0, strNum.find(".") + 4);
		} else {
			while(strNum.substr(strNum.find("."), strNum.length()).length() <= 3){
				//append
				strNum.append("0");
			}
		}
	}
	numStack.push(strNum);
}
void sub(){
	std::string strNum1 = numStack.top();
	numStack.pop();
	std::string strNum2 = numStack.top();
	numStack.pop();
	if(strNum1.find('.') != std::string::npos || strNum2.find('.') != std::string::npos){
		//if either is a double, must cast both as such
		double num1 = std::stod(strNum1);
		double num2 = std::stod(strNum2);
		double result = num1 - num2;
		std::cout << strNum1 << " - " << strNum2 << " = " << result << "\n";
		pushNum(std::to_string(result));
	} else {
		//else we cast both as int
		int num1 = std::stoi(strNum1);
		int num2 = std::stoi(strNum2);
		int result = num1 - num2;
		std::cout << strNum1 << " - " << strNum2 << " = " << result << "\n";
		pushNum(std::to_string(result));
	}
}

void add(){
	std::string strNum1 = numStack.top();
	numStack.pop();
	std::string strNum2 = numStack.top();
	numStack.pop();
	if(strNum1.find('.') != std::string::npos || strNum2.find('.') != std::string::npos){
		//if either is a double, must cast both as such
		double num1 = std::stod(strNum1);
		double num2 = std::stod(strNum2);
		double result = num1 + num2;
		std::cout << strNum1 << " + " << strNum2 << " = " << result << "\n";
		pushNum(std::to_string(result));
	} else {
		//else we cast both as int
		int num1 = std::stoi(strNum1);
		int num2 = std::stoi(strNum2);
		int result = num1 + num2;
		std::cout << strNum1 << " + " << strNum2 << " = " << result << "\n";
		pushNum(std::to_string(result));
	}
}

void mult(){
	std::string strNum1 = numStack.top();
	numStack.pop();
	std::string strNum2 = numStack.top();
	numStack.pop();
	if(strNum1.find('.') != std::string::npos || strNum2.find('.') != std::string::npos){
		//if either is a double, must cast both as such
		double num1 = std::stod(strNum1);
		double num2 = std::stod(strNum2);
		double result = num1 * num2;
		std::cout << strNum1 << " * " << strNum2 << " = " << result << "\n";
		pushNum(std::to_string(result));
	} else {
		//else we cast both as int
		int num1 = std::stoi(strNum1);
		int num2 = std::stoi(strNum2);
		int result = num1 * num2;
		std::cout << strNum1 << " * " << strNum2 << " = " << result << "\n";
		pushNum(std::to_string(result));
	}
}

void div(){
	std::string strNum1 = numStack.top();
	numStack.pop();
	std::string strNum2 = numStack.top();
	numStack.pop();
	if(strNum1.find('.') != std::string::npos || strNum2.find('.') != std::string::npos){
		//if either is a double, must cast both as such
		double num1 = std::stod(strNum1);
		double num2 = std::stod(strNum2);
		double result = num1 / num2;
		std::cout << strNum1 << " / " << strNum2 << " = " << result << "\n";
		pushNum(std::to_string(result));
	} else {
		//else we cast both as int
		int num1 = std::stoi(strNum1);
		int num2 = std::stoi(strNum2);
		int result = num1 / num2;
		std::cout << strNum1 << " / " << strNum2 << " = " << result << "\n";
		pushNum(std::to_string(result));
	}
}

void sqrt(){
	std::string strNum = numStack.top();
	numStack.pop();
	if(strNum.find('.') != std::string::npos){
		double num = std::stod(strNum);
		double result = sqrt(num);
		std::cout << "sqrt " << strNum << " = " << result << "\n";
		pushNum(std::to_string(result));  
	} else {
		int num = std::stoi(strNum);
		int result = sqrt(num);
		std::cout << "sqrt " << strNum << " = " << result << "\n";
		pushNum(std::to_string(result)); 
	}
}

void initRepeat(){
	//we initialise starting the repeat by setting loopNum
	std::string strNum = numStack.top();
	numStack.pop();
	int repeatNum = std::stoi(strNum);
	loopNum = repeatNum;
	storeRepeatFlag = true;
}

void executeRepeatSequence(){
	//goes through repQueue to execute commands. will re-add commands to queue as many times as specified
	//repSize is the size of the queue before re adding commands. We loop based on this, as its the number of
	//moves in the sequence
	const int repSize = repQueue.size();
	for(int i = 0; i < loopNum; i++){
		bool rePush = true;
		if(i == loopNum - 1){
			//will not re-add commands if last loop
			rePush = false;
		}
		for(int j = 0; j < repSize; j++){
			parseInput(repQueue.front());
			if(rePush == true){
				repQueue.push((repQueue.front()));
			}
			repQueue.pop();
		}
	}
}

void reverse(){
	//stores the commands to be reversed in a queue, then re pushes to stack in the queued order
	//this reverses the order
	std::string strNum = numStack.top();
	numStack.pop();
	int numReverse = std::stoi(strNum);
	std::queue<std::string> revQueue;
	for(int i = 0; i < numReverse; i++){
		revQueue.push(numStack.top());
		numStack.pop();
	}
	while(!revQueue.empty()){
		numStack.push(revQueue.front());
		revQueue.pop();
	}
}

























