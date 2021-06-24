#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>

int fact(int in) {
	int factorial = 1;
	for (int i = 1; i <= in; ++i) 
		factorial *= i;
	return factorial;
}

std::vector<int> _toFactSys(int num, const int& n) {
	std::vector<int> fact_ind;
	
	int factorial;
	int num_fact;
	for (size_t i = 1; ; i++)
	{
		factorial = fact(i);
		if (num < factorial) {
			factorial = fact(i - 1);
			num_fact = i - 1;
			break;
		}
	}
	for (size_t i = num_fact; i > 0; i--)
	{
		factorial = fact(i);
		fact_ind.push_back(num / factorial);
		num -= factorial * (num / factorial);
	}


	if (fact_ind.size() < n - 1) {
		std::reverse(fact_ind.begin(), fact_ind.end());
		for (size_t i = 0; i < fact_ind.size() - n + 1; ++i)
			fact_ind.push_back(0);
		std::reverse(fact_ind.begin(), fact_ind.end());
	}
	return fact_ind;
}

void TaskA(const int& n, const std::vector<char>& input, const int& ind, std::vector<char>& output, std::vector<int>& pi) {
	std::vector<int> fact_ind = _toFactSys(ind, n);

	if (!pi.empty()) pi.clear();
	
	std::cout << "N in factorial form: " << std::endl;
	for (size_t i = 0; i < fact_ind.size(); ++i) {
		std::cout << fact_ind[i];
	}
	pi.push_back(1);
	std::cout << std::endl;

	std::reverse(fact_ind.begin(), fact_ind.end());
	for (size_t i = 0; i < n - 1; ++i)
	{
		int dk = fact_ind[pi.size() - 1] + 1;
		std::cout << "d" << pi.size() - 1 << " = " << dk << std::endl;
		pi.push_back(dk);

		for (size_t j = 2; j <= pi.size(); j++)
		{
			std::cout << "\t";
			if (pi[pi.size() - j] >= dk) {
				std::cout << "(d" << pi.size() - 2 << " <= Pi" << pi.size() - j << ") => Pi" << pi.size() << " + 1" << std::endl;
				++pi[pi.size() - j];
			}
			else
				std::cout << "Pi" << pi.size() - j << " not change" << std::endl;
			std::cout << "\t";
			for (const auto& a : pi)
			{

				std::cout << input[a - 1] << " ";
			}
			std::cout << std::endl;
		}
	}
	std::reverse(pi.begin(), pi.end());

	for (size_t i = 0; i < pi.size(); ++i)
		output.push_back(input[pi[i] - 1]);
}


std::vector<int> TaskB(const std::vector<char>& input, std::vector<int> num_output, const int& n) {
	int i = 1;
	int j = 0;

	std::cout << "\t";
	for (const auto& a : num_output)
		std::cout << a << " ";
	std::cout << std::endl;

	i = n - 2;
	while (num_output[i] > num_output[i + 1]) --i;
	std::cout << "\tMax i: " << i << "\n\tElenemnt: " << num_output[i] << std::endl;

	j = n - 1;
	while (num_output[j] < num_output[i]) --j;
	std::cout << "\tMin j: " << j << "\n\tElenemnt: " << num_output[j] << std::endl;

	auto buf = num_output[j];
	num_output[j] = num_output[i];
	num_output[i] = buf;

	std::cout << "\tSwap(Pi[i], Pi[j])" << std::endl;
	std::cout << "\t";
	for (const auto& a : num_output)
		std::cout << a << " ";
	std::cout << std::endl;

	std::cout << "\tReverse Pi[i + 1] to Pi[n]" << std::endl;
	std::reverse(num_output.begin() + i + 1, num_output.end());
	std::cout << "\t";

	for (const auto& a : num_output)
		std::cout << a << " ";
	std::cout << std::endl;

	return num_output;
}


int ind_p(std::vector<int> pi, int i = 0) {
	for (size_t j = i + 1; j < pi.size(); ++j)
		pi[j] = (pi[j] > pi[i]) ? pi[j] - 1 : pi[j];
	return (pi.size() - i == 1) ? 0 : fact(pi.size() - i - 1) * (pi[i] - 1) + ind_p(pi, i + 1);
}



void Task1() {
	system("cls");
	std::cout << "Task 1" << std::endl;
	char buf;
	int n, ind;
	std::vector<char> input;
	std::vector<int> numeric_output;
	std::vector<int> numeric_outputB;
	std::vector<char> output;



	std::cout << "Count of elements(num of el in A)" << std::endl;
	std::cin >> n;
	std::cout << "Write your massive(A): " << std::endl;
	for (size_t i = 0; i < n; ++i) {
		std::cin >> buf;
		input.push_back(buf);
	}
	std::cout << "Your index(N)" << std::endl;
	std::cin >> ind;

	std::cout << std::endl;
	std::cout << "Task 1a" << std::endl;
	TaskA(n, input, ind, output, numeric_output);

	std::cout << std::endl;
	for (const auto& a : output)
	{
		std::cout << a << " ";
	}
	std::cout << std::endl;

	std::cout << "Task 1b" << std::endl;
	numeric_outputB = numeric_output;

	for (size_t i = 2; i < 5; i++)
	{
		std::cout << "Pi" << i << std::endl;
		numeric_outputB = TaskB(input, numeric_outputB, n);
		for (const auto& a : numeric_outputB)
		{
			std::cout << input[a - 1] << " ";
		}
		std::cout << std::endl;
	}

	std::cout << "Task 1c" << std::endl;
	std::cout << ind_p(numeric_outputB) << std::endl;
	system("pause");
}



void Task2() {
	system("cls");
	std::cout << "Task 2" << std::endl;
	char buf;
	int n, num_buf;
	std::vector<char> input;
	std::vector<char> A;
	std::vector<int> input_reverse;
	std::vector<int> d;
	std::vector<int> numeric_input;
	std::vector<char> output;
	std::cout << "Count of elements(num of el in Pi5)" << std::endl;
	std::cin >> n;

	std::cout << "Write your massive(Pi5): " << std::endl;
	for (size_t i = 0; i < n; ++i) {
		std::cin >> buf;
		input.push_back(buf);
		A.push_back('a' + i);
		numeric_input.push_back((int)input[i] - (int)'a' + 1);
	}

	std::cout << "Write your d: " << std::endl;
	for (size_t i = 0; i < n; ++i) {
		std::cin >> num_buf;
		d.push_back(num_buf);
	}


	input_reverse = numeric_input;
	for (size_t i = 0; i < n; ++i) {
		input_reverse[numeric_input[i] - 1] = (int)A[i] - (int)'a' + 1;
	}
	std::cout << "P: ";
	for (auto a : input_reverse)
	{
		std::cout << a << " ";
	}
	std::cout << std::endl;

	for (auto a : input_reverse) {
		std::cout << a << " ";
	}
	std::cout << std::endl;
	for (size_t k = 1; k <= 3; ++k) {
		std::cout << "Pi" << 5 + k << std::endl;
		int m = n;
		numeric_input.push_back(n + 1);
		std::reverse(numeric_input.begin(), numeric_input.end());
		numeric_input.push_back(n + 1);
		std::reverse(numeric_input.begin(), numeric_input.end());
		std::cout << "m = " << m << std::endl;
		std::cout << "\td:";
		for (const auto& a : d) {
			std::cout << a << " ";
		}
		std::cout << std::endl;
		std::cout << "WHILE: " << numeric_input[input_reverse[m - 1] + d[m - 1]] << ">?" << m << std::endl;
		while (numeric_input[input_reverse[m - 1] + d[m - 1]] > m) {
			std::cout << "\tPi[(P[m]=" << input_reverse[m - 1] << ") + (d[m]=" << d[m - 1] << ")] > m: " << numeric_input[input_reverse[m - 1] + d[m - 1]] << " > " << m << std::endl;
			std::cout << "\td[m] = -d[m] and m = m - 1" << std::endl;
			d[m - 1] = -d[m - 1];
			--m;
			std::cout << "m = " << m << std::endl;
			std::cout << "\td:";
			for (const auto& a : d) {
				std::cout << a << " ";
			}
			std::cout << std::endl;
		}
		std::cout << "swap(Pi[P[" << m << "]]=" << numeric_input[input_reverse[m - 1]] << ", Pi[P[" << m <<"] + d[" << m <<"]]=" 
												<< numeric_input[input_reverse[m - 1] + d[m - 1]] << ")" << std::endl;
		auto buffer = numeric_input[input_reverse[m - 1]];
		numeric_input[input_reverse[m - 1]] = numeric_input[input_reverse[m - 1] + d[m - 1]];
		numeric_input[input_reverse[m - 1] + d[m - 1]] = buffer;

		std::cout << "swap(P[Pi[P[" << m << "]="<< input_reverse[m - 1] <<"]=" << numeric_input[input_reverse[m - 1]] <<"]=" 
				  << input_reverse[numeric_input[input_reverse[m - 1]] - 1] << ", P[" << m << "] =" << input_reverse[m - 1] << ")"<< std::endl;
		buffer = input_reverse[numeric_input[input_reverse[m - 1]] - 1];
		input_reverse[numeric_input[input_reverse[m - 1]] - 1] = input_reverse[m - 1];
		input_reverse[m - 1] = buffer;

		numeric_input.erase(numeric_input.begin());
		numeric_input.pop_back();
		std::cout << "\tResult vector in numbers" << std::endl;
		std::cout << "\t";
		for (const auto& a : numeric_input)
		{
			std::cout << a << " ";
		}
		std::cout << std::endl;
		std::cout << "\tResult vector in chars" << std::endl;
		std::cout << "\t";
		for (const auto& a : numeric_input)
		{
			std::cout << A[a - 1] << " ";
		}
		std::cout << std::endl;
		/*for (size_t i = 0; i < n; ++i) {
			input_reverse[numeric_input[i] - 1] = (int)A[i] - (int)'a' + 1;
		}*/
		std::cout << "\tReversed vector(P): " << std::endl;
		std::cout << "\t";
		for (const auto& a : input_reverse)
		{
			std::cout << A[a - 1] << " ";
		}
		std::cout << std::endl;
	}
	system("pause");
}


std::vector<int> _to_binary(int num) {
	std::vector<int> binary;
	for (int i = sizeof(num) * 2 - 1; i >= 0; --i)
	{
		binary.push_back( (int)((num >> i) & 1));
	}
	return binary;
}

int _to_dex(const std::vector<int>& bin) {
	int dex = 0;
	for (size_t i = 1; i <= bin.size(); i++)
		dex += (bin[i - 1]) ? pow(2, bin.size() - i) : 0;
	return dex;
}


void Task3() {
	system("cls");
	std::cout << "Task 1" << std::endl;
	std::cout << "Task 3a" << std::endl;
	char buf;
	int n;
	std::vector<char> A;
	std::vector<int> B_Vec;
	std::vector<char> output;
	std::vector<char> B;
	std::cout << "Count of elements(num of el in A)" << std::endl;
	std::cin >> n;
	std::cout << "Write your massive(A): " << std::endl;
	for (size_t i = 0; i < n; ++i) {
		std::cin >> buf;
		A.push_back(buf);
	}
	int M;
	std::cout << "Write your M:" << std::endl;
	std::cin >> M;
	B_Vec = _to_binary(M);
	std::reverse(B_Vec.begin(), B_Vec.end());
	if (B_Vec.size() < A.size()) {
		std::reverse(B_Vec.begin(), B_Vec.end());
		for (size_t i = 0; i < A.size() - B_Vec.size(); i++)
			B_Vec.push_back(0);
		std::reverse(B_Vec.begin(), B_Vec.end());
	}
	std::cout << "\tA massive and M in binary, create result: " << std::endl;
	std::cout << "\t";
	for (const auto& a : A)
	{
		std::cout << a << " ";
	}
	std::cout << std::endl;
	std::cout << "\t";
	for (const auto& a : B_Vec)
	{
		std::cout << a << " ";
	}
	std::cout << std::endl;

	for (size_t i = 0; i < A.size(); i++)
		if (B_Vec[i]) output.push_back(A[i]);
	std::cout << "\nOutput: " << std::endl;
	for (const auto& a : output)
	{
		std::cout << a << " ";
	}
	std::cout << std::endl;

	std::cout << "Task 3b" << std::endl;

	std::cout << "Count of elements(num of el in B)" << std::endl;
	std::cin >> n;
	std::cout << "Write your massive(B): " << std::endl;
	for (size_t i = 0; i < n; ++i) {
		std::cin >> buf;
		B.push_back(buf);
	}

	B_Vec.clear();

	for (size_t i = 0; i < A.size(); ++i) {
		if (std::find(B.begin(), B.end(), A[i]) != B.end()) B_Vec.push_back(1);
		else B_Vec.push_back(0);
	}
	std::reverse(B_Vec.begin(), B_Vec.end());
	std::cout << "Like 3a" << std::endl;
	std::cout << "\trun in A, if Elelemnt is in B - that 1, else 0(make binary lexical number). And read from right to left" << std::endl;
	std::cout << "Lexical number in binary: " << std::endl;

	for (const auto& a : B_Vec)
	{
		std::cout << a << " ";
	}
	std::cout << std::endl;
	std::cout << "Lexical number in dex: " << _to_dex(B_Vec) << std::endl;
	system("pause");
}

void Task4() {
	system("cls");
	std::cout << "Task 4" << std::endl;
	std::vector<int> T_B;
	std::vector<int> T_B_bit_r;
	std::vector<int> G;
	int T, n = 8;
	std::cout << "Write your T: " << std::endl;
	std::cin >> T;
	for (size_t j = 0; j <= 3; j++)
	{
		T_B = _to_binary(T);
		if (T_B.size() < 9) {
			std::reverse(T_B.begin(), T_B.end());
			for (size_t i = 0; i < 9 - T_B.size(); i++)
				T_B.push_back(0);
			std::reverse(T_B.begin(), T_B.end());
		}

		T_B_bit_r = T_B;
		(std::find(T_B_bit_r.begin(), T_B_bit_r.end(), 0) != T_B_bit_r.end()) ? T_B_bit_r.erase(std::find(T_B_bit_r.begin(), T_B_bit_r.end(), 0))
			:
			T_B_bit_r.erase(T_B_bit_r.begin());


		std::cout << "T = " << T << " = (bin)";
		for (const auto& a : T_B)
		{
			std::cout << a << " ";
		}
		std::cout << std::endl;

		std::cout << "T bit right(>>)" << " = (bin)";
		for (const auto& a : T_B_bit_r)
		{
			std::cout << a << " ";
		}
		std::cout << std::endl;

		std::cout << "\tMake sum (T bit right[i] + T[i])mod2" << std::endl;

		for (size_t i = 0; i < n; i++)
		{
			G.push_back((T_B_bit_r[i] + T_B[i]) % 2);
			std::cout << "\tT_B_bit_r[" << i << "] = " << T_B_bit_r[i] << std::endl;
			std::cout << "\t(bit)T[" << i << "] = " << T_B[i] << std::endl;
			std::cout << "\tT_B_bit_r[" << i << "] + (bit)T[" << i << "] = " << T_B_bit_r[i] << " +(mod 2) "
				<< T_B[i] << " = " << (T_B_bit_r[i] + T_B[i]) % 2 << std::endl;
		}
		std::cout << "\nG" << j + 1 << ": ";
		for (const auto& a : G)
		{
			std::cout << a << " ";
		}
		std::cout << std::endl;
		++T;
		G.clear();
		T_B_bit_r.clear();
		T_B.clear();
	}
	system("pause");
}

void Task5() {
	system("cls");
	std::cout << "Task 5" << std::endl;
	int n;
	char buf;
	std::vector<char> B;
	std::vector<int> B_I;
	std::vector<char> A;

	std::cout << "Count of elements(num of el in A)" << std::endl;
	std::cin >> n;
	std::cout << "Write your massive(A): " << std::endl;
	for (size_t i = 0; i < n; ++i) {
		std::cin >> buf;
		A.push_back(buf);
	}

	std::cout << "Count of elements(num of el in B)" << std::endl;
	std::cin >> n;
	std::cout << "Write your massive(B): " << std::endl;
	for (size_t i = 0; i < n; ++i) {
		std::cin >> buf;
		B.push_back(buf);
	}

	for (size_t k = 0; k < 3; ++k) {
		std::cout << "C" << k << " (C0 == B)" << std::endl;
		for (const auto& a : B)
		{
			std::cout << a << " ";
		}
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		int j = B.size() - 1;
		std::cout << "\tStart search minimal element from right to left(start: B.size())" << std::endl;
		while ((int)B[j] - (int)A[0] + 1 == ((int)A[A.size() - 1] - (int)A[0] + 1) - (B.size() - 1) + j) --j;
		std::cout << "\tMinimal element postion = " << j << std::endl;
		std::cout << "\tMinimal element = " << B[j] << std::endl;
		++B[j];
		std::cout << "\tmin elemnt + 1" << std::endl;
		std::cout << "\tYour C massive after + 1 to min elemnt" << std::endl;
		std::cout << "\t";
		for (const auto& a : B)
		{
			std::cout << a << " ";
		}
		std::cout << std::endl;

		std::cout << "\tNext elemnts it's our j elemnt + i, where i from j + 1(first after j) to B.size(last element)" << std::endl;
		for (size_t i = j + 1; i < B.size(); i++)
		{
			B[i] = B[i - 1] + 1;
			std::cout << "\tMake + 1 to C[i+1]" << std::endl;
			std::cout << "\t";
			for (const auto& a : B)
			{
				std::cout << a << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	std::cout << "C3" << std::endl;
	for (const auto& a : B)
	{
		std::cout << a << " ";
	}
	std::cout << std::endl;
	std::cout << std::endl;
	system("pause");
}


int main() {
	int buf = 1;
	while (buf != 0)
	{
		system("cls");
		std::cout << "What task do you need to decide?" << std::endl;
		std::cout << "Task1 - press key '1'" << std::endl;
		std::cout << "Task2 - press key '2'" << std::endl;
		std::cout << "Task3 - press key '3'" << std::endl;
		std::cout << "Task4 - press key '4'" << std::endl;
		std::cout << "Task5 - press key '5'" << std::endl;
		std::cout << "Exit - press key '0'" << std::endl;
		std::cin >> buf;
		switch (buf)
		{
		case 1:
			Task1();
			break;
		case 2:
			Task2();
			break;
		case 3:
			Task3();
			break;
		case 4:
			Task4();
			break;
		case 5:
			Task5();
			break;
		default:
			buf = 0;
			break;
		}

	}

	system("cls");
	return 0;
}
