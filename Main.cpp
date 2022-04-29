#include <iostream>
#include<vector>
using namespace std;
class Sequence;
class Task;
class PrintTask;

class Sequence {
public:
	Sequence();
	void runTasks();
	void addTask(Task* task);
private:
	int index = 0;
	Task* currentTask = nullptr;
	vector<Task*> tasks;
	int taskSize = 0;
};
class Task {
public:
	enum class Result
	{
		Succeeded,
		Failed,
		InProgress,
	};
	Result result;
	Task();
	virtual void executeTask();
};
Task::Task()
{
	result = Result::InProgress;
}
void Task::executeTask()
{



}
Sequence::Sequence()
{

	taskSize = tasks.size();
	index = -1;

}
void Sequence::runTasks()
{
	while (index < taskSize) {
		index += 1;
		if (index >= taskSize) {
			return;
		}
		currentTask = tasks[index];
		currentTask->executeTask();
		while (currentTask->result != Task::Result::Succeeded)
		{
			if (currentTask->result == Task::Result::InProgress) { continue; }
			else { index = 9000; return; }
		}
	}

}
void Sequence::addTask(Task* task)
{
	tasks.push_back(task);
	taskSize = tasks.size();
}
class PrintTask :public Task {
private:
	const int size;
public:

	PrintTask(string message, const int _size);
	virtual void executeTask() override;
	string message;

};
PrintTask::PrintTask(string message, const int _size) :size(_size)
{
	this->message = message;
}
void PrintTask::executeTask()
{
	for (int i = 0; i < size; i++)
	{
		cout << message << endl;
	}
	result = Task::Result::Succeeded;
}
int main()
{
	Task* pt = new PrintTask("Hello", 5);
	Task* pt1 = new PrintTask("Hi", 4);
	Task* pt2 = new PrintTask("Good Morning", 4);

	Sequence* s = new Sequence();
	s->addTask(pt);
	s->addTask(pt1);
	s->addTask(pt2);
	s->runTasks();

	return 0;

}

