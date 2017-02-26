#include<iostream>
#include<fstream>
#include"stdlib.h"
#include"math.h"

using namespace std;
//����������㺯�� 
double* findA(double x[100][3],double theta[3]) {
	double *data3 = new double[100];
	double tmp;
	int i,j;
	for(i = 0;i<100;i++){
		tmp = 0;
		for(j = 0;j<3;j++){
			tmp=x[i][j]*theta[j]+tmp;
		}
		data3[i] = tmp;
	}
	return data3;
}

double sigmoid(double m){
	double tmp = exp(-m);
	double tmp2 = 1/double(1+tmp);
	return tmp2;
}

double *findE(double ga[100],int y[101]){
	double *data5 = new double [100];
	int i;
	for(i = 0;i<100;i++)
	data5[i] = ga[i] - y[i];
	return data5;
}

double* findGa(double A[100]) {
	int i;
	double *data4  = new  double [100];
	for(i = 0;i<100;i++)
	data4[i] = sigmoid(A[i]);
	return data4;
}

double*findXE(double X[100][3],double e[100]){
	double *data6 = new double[3];
	int i,j;
	double tmp;
	for(i = 0;i<3;i++){
		tmp = 0;
		for(j = 0;j<100;j++){
			tmp = tmp+X[j][i]*e[j];
		}
		data6[i] = tmp;
	}
	return data6;
}

double findcost( double ga[100],int y[101]){
	double cost = 0;
	int i;
	for(i = 0;i<100;i++) {
	    cost = cost + y[i]*log(ga[i])+(1-y[i])*log(1-ga[i]);
	}
	cost = -cost/100;
	return cost;
}

int main() {
	double data[201];
	double data2[100][3];//����x(����)��100*3�ľ��󣬵�һ��Ϊ1
	int y[101];//1��0������� 
	double *A;//����A����X*theta 
	double *ga;//����ga����g(A),����g(z)Ϊsigmoid���� 
	double *error;//����errorΪg(A)-y 
	double *xe;//����xe
	double alpha;//3����� 
	double theta[3];//��ʼֵ����;
	int test[100];//��y[100]���Ƚ� 
	int testout[100];
	int i = 0,j = 0,m = 0,n = 0;
	fstream in;
	in.open("data/LR_TrainingSet.txt",ios::in);
	if(!in.is_open()){
		cout<<"Error\n";
		exit(1);
	}
	//�����ݵ������� 
	while(!in.eof()){
		if(m%3!=2) {
		    in>>data[i];
		    i++;
		    in.get();//ȥ���ָ��� 
		} else {
			in>>y[j];
			j++;
			in.get();//ȥ���ָ��� 
		}
		m++;
	}
	in.close();
	m = 0;
	//�����ݵ���100*3�����飬����ÿһ���һ����Ϊ1 
	for (i = 0;i<100;i++){
		data2[i][0] = 1;
		for(j = 1;j<3;j++){
			data2[i][j] = data[m];
			m++;
		}	
	}
	cout<<"Please input 3 numbers to predict the theta\n";
	for(i = 0;i<3;i++)
	cin>>theta[i];
	cout<<"Please input estimated alpha\n";
	cin>>alpha;
    A = findA(data2,theta);
	ga = findGa(A);
    error = findE(ga,y);
	xe = findXE(data2,error);
	for(i = 0;i<3;i++){ //����theta 
		theta[i] = theta[i] - alpha*xe[i]/100;
	}
	A = findA(data2,theta);
	ga = findGa(A);
    j = 0;
    double oldtheta[3]; 
	while(j<400) {
		for(i=0;i<3;i++)
		oldtheta[i] = theta[i];
        error = findE(ga,y);
        xe = findXE(data2,error);
        for(i = 0;i<3;i++) //����theta 
		theta[i] = theta[i] - alpha*xe[i]/100;
		A = findA(data2,theta);
		ga = findGa(A);
		j++;
		m = 0;
		for(i = 0;i<3;i++){
			if(fabs(oldtheta[i]-theta[i])<0.0001)
			m++;
		}
		if(m ==3 )
		break;
	}
	cout<<"iteration number: \n"<<j<<endl;
	cout<<"theta: \n";
	for(i = 0;i<3;i++)
	cout<<theta[i]<<' ';
	cout<<endl;
	for(i = 0;i<100;i++){//Ԥ��ֵ 
		if(ga[i]>=0.5)
		test[i] = 1;
		else
		test[i] = 0;
	}
	for(i = 0;i<100;i++){//��y���Ƚ� 
		if(test[i] == y[i])
		n++;
	}
	cout<<"The accuracy rate is : "<<(double)n/100;//��ȷ��
	cout<<"\n";
	cout<<"Please enter 1 to predict the testdata, 0 to exit\n";
	cin>>n;
	if(n == 0){
	    exit(1);
	} else {
		fstream in2;
		in2.open("data/LR_TestingSet.txt",ios::in);
		if(!in2.is_open()){
			cout<<"Error\n";
			exit(2);
		}
		i = 0;
		while(!in2.eof()){
			in2>>data[i];
			if(i%2 == 0){//�����ָ�����test�ļ��ϸ��� 
				in2.get();
				in2.get();
				in2.get();
				in2.get();
			} else {
				in2.get();
			}
			i++;
		}
		in2.close();
		m = 0;
		for (i = 0;i<100;i++){
		    data2[i][0] = 1;
		    for(j = 1;j<3;j++){
			    data2[i][j] = data[m];
			    m++;
		    }	
	    }  
        A = findA(data2,theta);//theta�Ѹ��� 
	    ga = findGa(A);
	    for(i = 0;i<100;i++){
		    if(ga[i]>=0.5)
		    testout[i] = 1;
	        else
		    testout[i] = 0;
	    }
	    cout<<"Prediction result: \n";
	    for(i = 0;i<100;i++)
	    cout<<testout[i]<<' ';
	}
	cout<<'\n';
	//��Ԥ����������ı��������µ��ı� 
	string str;
	fstream in3,fout;
	in3.open("data/LR_TestingSet.txt",ios::in);
	fout.open("data/LR_TestingOutSet.txt",ios::out);
	i = 0;
	while(getline(in3,str)){
		char* sb;
		itoa(testout[i],sb,10);
		str = str + ','+sb+'\n';
		fout<<str;
		i = i+1;
	}
	in3.close();
	fout.close();
	cout<<"Testout file creates in the disk successfully!\n";
	return 0;
}


