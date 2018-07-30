#include "test_framework/generic_test.h"
#include "test_framework/serialization_traits.h"
#include "test_framework/test_failure.h"
#include <vector>
using namespace std;

class Queue {
public:
	Queue(size_t capacity):_data(capacity) {}
	void Enqueue(int x) {
		if (cnt == _data.size()) {
			rotate(_data.begin(), _data.begin() + head, _data.end());
			_data.resize(_data.size() * 2);
			head = 0;
			tail = cnt;
		}
		_data[tail++] = x;
		cnt++;
		tail %= _data.size();
	}
	int Dequeue() {
		if (cnt == 0)
			throw length_error("null stack");
		int temp = _data[head++];
		head %= _data.size();
		cnt--;
		if (_data.size() / 2 > cnt && cnt > 0) {
			rotate(_data.begin(), _data.begin() + head, _data.end());
			_data.resize(_data.size() / 2);
			tail = cnt % _data.size();
			head = 0;
		}
		return temp;
	}
	int Size() const {
		return cnt;
	}
private:
	vector<int> _data;
	int head = 0, tail = 0, cnt = 0;
};
struct QueueOp {
	enum { kConstruct, kDequeue, kEnqueue, kSize } op;
	int argument;

	QueueOp(const std::string& op_string, int arg) : argument(arg) {
		if (op_string == "Queue") {
			op = kConstruct;
		}
		else if (op_string == "dequeue") {
			op = kDequeue;
		}
		else if (op_string == "enqueue") {
			op = kEnqueue;
		}
		else if (op_string == "size") {
			op = kSize;
		}
		else {
			throw std::runtime_error("Unsupported queue operation: " + op_string);
		}
	}

	void execute(Queue& q) const {
		switch (op) {
		case kConstruct:
			// Hack to bypass deleted assign operator
			q.~Queue();
			new (&q) Queue(argument);
			break;
		case kDequeue: {
			int result = q.Dequeue();
			if (result != argument) {
				throw TestFailure("Dequeue: expected " + std::to_string(argument) +
					", got " + std::to_string(result));
			}
		} break;
		case kEnqueue:
			q.Enqueue(argument);
			break;
		case kSize: {
			int s = q.Size();
			if (s != argument) {
				throw TestFailure("Size: expected " + std::to_string(argument) +
					", got " + std::to_string(s));
			}
		} break;
		}
	}
};

template <>
struct SerializationTraits<QueueOp> : UserSerTraits<QueueOp, std::string, int> {
};

void QueueTester(const std::vector<QueueOp>& ops) {
	Queue q(0);
	for (auto& op : ops) {
		op.execute(q);
	}
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args{ argv + 1, argv + argc };
	std::vector<std::string> param_names{ "ops" };
	return GenericTestMain(args, "circular_queue.cc", "circular_queue.tsv",
		&QueueTester, DefaultComparator{}, param_names);
}
