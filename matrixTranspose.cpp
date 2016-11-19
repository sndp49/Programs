#include <iostream>
#include <vector>
using namespace std;

void printMat(const vector<vector<int>>& mat)
{
	for (int i=0; i<mat.size(); i++)
	{
		for (int j=0; j<mat[i].size(); j++)
			cout << mat[i][j] << ", ";
		cout << endl;
	}
}

void printMatTranspose(const vector<vector<int>>& mat)
{
	int m = mat.size(), n = mat[0].size();

	for (int j=0; j<n; j++)
	{
		for (int i=0; i<m; i++)
			cout << mat[i][j] << ", ";
		cout << endl;
	}
}

void init(vector<vector<int>>& mat)
{
	srand(time(NULL));

	for (int i=0; i<mat.size(); i++)
	{
		for (int j=0; j<mat[i].size(); j++)
			mat[i][j] = rand()%37;
	}
}

void transposeSQ(vector<vector<int>>& mat)
{
	for (int i=0; i<mat.size(); i++)
	{
		for (int j=i+1; j<mat[i].size(); j++)
			swap(mat[i][j], mat[j][i]);
	}
}

void transpose(vector<vector<int>>& mat)			// m < n
{
	int m = mat.size(), n = mat[0].size();

	for (int i=0; i<n-m; i++)				// add rows to the end with m cols. Only m are added because in the final matrix, we will have m cols at max
		mat.push_back(vector<int>(m, 0));

	for (int i=0; i<m; i++)
	{
		for (int j=i+1; j<n; j++)
			swap(mat[i][j], mat[j][i]);
	}

	for (int i=0; i<m; i++)					// delete the extra columns
		mat[i].erase(mat[i].begin()+m, mat[i].end());
}

void transpose(vector<vector<int>>& mat, int a)		// m > n
{
	int m = mat.size(), n = mat[0].size();

	for (int i=0; i<m; i++)
	{
		for (int j=0; j<i; j++)
		{
			if (i>=mat[j].size())
				mat[j].push_back(mat[i][j]);
			else
				swap(mat[i][j], mat[j][i]);
		}
	}

	mat.erase(mat.begin()+n, mat.end());
}


int main(int argc, char* argv[])
{
	int m = 4, n = 3;

	if (argc==3) {
		m = atoi(argv[1]);
		n = atoi(argv[2]);
	}

	vector<vector<int>> mat(m, vector<int>(n));

	init(mat); printMat(mat); cout << "\n---------------------------------------------\n" << endl; //printMatTranspose(mat); cout << "\n---------------------------------------------\n" << endl;

	if (m==n)
		transposeSQ(mat);
	else
		(m<n) ? transpose(mat) : transpose(mat, 0);

	printMat(mat);
	return 0;
}
