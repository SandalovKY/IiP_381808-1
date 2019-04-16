#include "FilmLibrary.h"

FilmLib::FilmLib() // ����������� �� ���������
{
	count = 0;
	buffSize = 0;
	FilmArray = new Film [buffSize];
}

FilmLib::FilmLib(const FilmLib& _flmlb) // ����������� �����������
{
	count = _flmlb.count;
	buffSize = _flmlb.buffSize;
	FilmArray = new Film[buffSize];
	for (int i = 0; i < count; ++i)
	{
		FilmArray[i] = _flmlb.FilmArray[i];
	}
}

FilmLib::~FilmLib() // ����������
{
	delete[] FilmArray;
}

FilmLib& FilmLib::operator= (const FilmLib& _flmlb)  // ���������� �������� ������������
{
	if (&_flmlb != this)
	{
		if (buffSize < _flmlb.buffSize)
		{
			FilmArray = new Film[_flmlb.buffSize];
		}
		buffSize = _flmlb.buffSize;
		count = _flmlb.count;
		for (int i = 0; i < count; ++i)
		{
			FilmArray[i] = _flmlb.FilmArray[i];
		}
	}
	return *this;
}

void FilmLib::AddFilm(const Film& _flm) // ���������� ������ � ����������
{
	// ����������� �������, �� ������� ���������� ��������� ����� � �������
	int i = 0; 
	while (FilmArray[i].name <_flm.name && i < count)
	{
		++i;
	}
	while (_flm.name == FilmArray[i].name && (_flm.year * 365 + _flm.month * 30 + _flm.day > FilmArray[i].year * 365 + FilmArray[i].month * 30 + FilmArray[i].day))
		++i;
	
	count++;
	if (buffSize <= count)
	{
		Film *tempArr;
		buffSize = count + 100;
		tempArr = new Film[buffSize];
		int j = 0;
		for (; j < i; ++j)
		{
			tempArr[j] = FilmArray[j];
		}
		tempArr[j++] = _flm;
		while (j++ < count)
		{
			tempArr[j] = FilmArray[j - 1];
		}
		delete[] FilmArray;
		FilmArray = tempArr;
	}
	else
	{
		for (int j = count - 2; j >= i; --j) // ������������ ����� ���� ��������� � �����, �� ������� ���������� �������� ����� ������� 
		{
			FilmArray[j + 1] = FilmArray[j];
		}
		FilmArray[i] = _flm;
	}


}

ostream& operator<< (ostream& _out, const FilmLib& _flmlb) // ���������� �������� ������ � �����
{

	for (int i = 0; i < _flmlb.count - 1; ++i)
	{
		_out << _flmlb.FilmArray[i] << '\n';
	}
	_out << _flmlb.FilmArray[_flmlb.count - 1];
	
	return _out;
}

istream& operator>> (istream& _inStream, FilmLib& _flmlb) // ������ �� ������
{
	Film flm;
	while (_inStream >> flm)
	{
		
		_flmlb.AddFilm(flm);
		
	}
	
	return _inStream;
}

int FilmLib::NameSearch(const string& _name) // ����� ������ �� ��� �������� (�������� �����)
{
	int left = 0, right = count - 1;

	while (left <= right)
	{
		int mid = (left + right) / 2;
		if (FilmArray[mid].name == _name)
		{
			return mid;
		}

		if (FilmArray[mid].name < _name)
		{
			left = mid + 1;
		}
		else
		{
			right = mid - 1;
		}
		
	}
	
	return -1;
}

Film* FilmLib::ProducerSearch(const string& _name, int* _num , Film* _flm) // ����� ���� ������� ������ ���������
{
	// ������� ������� ����� ���� ������� ����� ���������
	int num = 0;
	for (int i = 0; i < count; ++i)
	{
		if (_name == FilmArray[i].producer)
			num++;
	}
	_flm = new Film[num]; // �������� ��� ��� ������ ����������� ���-�� ������
	*_num = num;
	num = 0;
	for (int i = 0; i < count; ++i) // ��������� ��� ������ � ���� ����� ������
	{
		if (_name == FilmArray[i].producer)
		{
			_flm[num] = FilmArray[i];
			num++;
		}
	}
	return _flm;
}

Film* FilmLib::TimeSearch(int _year, int* _num, Film *_flm) // ����������
{
	int cnt = 0;
	for (int i = 0; i < count; ++i)
	{
		if (FilmArray[i].year == _year)
			cnt++;
	}
	_flm = new Film[cnt];
	*_num = cnt;
	cnt = 0;
	for (int i = 0; i < count; ++i)
	{
		if (FilmArray[i].year == _year)
		{
			_flm[cnt] = FilmArray[i];
			cnt++;
		}
	}
	return _flm;
}

void FilmLib::ChangeSelectedFilm(const Film& _flm, int _cnt) // ������ ���������� � �������� ������
{
	FilmArray[_cnt] = _flm;
}

int FilmLib::GetCount() // ���������� ���������� ������� � ����������
{
	return count;
}

void FilmLib::DeleteSelectedFilm(int _cnt) // ������� ���������� ������
{

	for (int i = _cnt; i < count - 1; ++i)
		FilmArray[i] = FilmArray[i + 1];
	count--;

}

void FilmLib::MaxBoxOffice(int *_num, Film *flm) // ����� ������������� ����� ������� � ����������� �������� �������
{
	int cnt = 0;
	int maxBoxOffice = LONG_MAX;
	int _cnt = 0;
	while (cnt < *_num) // ���� ����� ��������� ������� ������ ��������� ��������� �����
	{
		for (int i = 0; i < count; ++i) //������� ���� �����(�������� ������) � �������� ���� �������, ��� ��� ������ ���� ��������� �����
		{                               // ���� ����� ������ ���� ���������, �� ������ ��� ���������� ���������(maxBoxOffice), �� ��������� ��� � ��� ������ � ������ ��������
			if (FilmArray[i].box_office < maxBoxOffice)
			{
				bool ch = true;
				for (int j = 0; j < count; ++j)
				{
					if (FilmArray[j].box_office < maxBoxOffice && FilmArray[i].box_office < FilmArray[j].box_office)
						ch = false;
				}
				if (ch)
				{
					maxBoxOffice = FilmArray[i].box_office;
					flm[cnt] = FilmArray[i];
					cnt++;
					
				}
			}
			
		}
		_cnt++; 
		if (_cnt > count) // ��� ������ ��������� ��� ��������� ������, � ����� ���������� ������ ��������� �����, ���������� ���� � ������� ���, ��� ����
		{
			*_num = cnt;
			cout << "� ���������� ��� ������������ ����� �������" << '\n';
			cout << "��� ���, ��� ����: " << '\n';
			return;
		}
	}

}

void FilmLib::MaxBoxOffice(int *_num, Film *flm, const int& _year) // ���������� ����������� ������
{
	int cnt = 0;
	int _cnt = 0;
	int maxBoxOffice = LONG_MAX;
	while (cnt < *_num)
	{
		for (int i = 0; i < count; ++i)
		{
			if (FilmArray[i].box_office < maxBoxOffice && FilmArray[i].year == _year)
			{
				bool ch = true;
				for (int j = 0; j < count; ++j)
				{
					if (FilmArray[j].box_office < maxBoxOffice && FilmArray[j].year == _year && FilmArray[i].box_office < FilmArray[j].box_office)
						ch = false;
				}
				if (ch)
				{
					
						maxBoxOffice = FilmArray[i].box_office;
						flm[cnt] = FilmArray[i];
						cnt++;
					
				}
			}
		}
		_cnt++;
		if (_cnt > count)
		{
			*_num = cnt;
			cout << "� ���������� ��� ������������ ����� �������"<<'\n';
			cout << "��� ���, ��� ����: " << '\n';
			return;
		}
	}
		
	
}

int StrToInt(const string& _str) // ������ �������� �������� ���������� ����������, ���������� ���������� � ����� � ���������� ���� int
{
	int sum = 0;
	for (int i = 0; i < _str.length(); ++i)
	{
		sum = sum * 10 + (_str[i] - '0');
	}
	return sum;
}

Film FilmLib::GetFilm(const int _count) // ����� ���������� ���������� �� ����� ������ �� ����������
{
	return FilmArray[_count];
}

ostream& operator<< (ostream& _out, const Film& _flm) // ���������� �������� ������ � ����� � ������ �� ���� ��� ��������
{
	_out << _flm.name << ';' << _flm.producer << ';' << _flm.swriter << ';' << _flm.composer << ';' << _flm.day << ';' << _flm.month << ';' << _flm.year << ';' << _flm.box_office ;
	return _out;
}

istream& operator>> (istream& _in, Film& _flm)
{
	char in[256];
	
	if (_in.getline(in, 256, ';'))
	{
		_flm.name = in;
		_in.getline(in, 256, ';');
		_flm.producer = in;
		_in.getline(in, 256, ';');
		_flm.swriter = in;
		_in.getline(in, 256, ';');
		_flm.composer = in;
		_in.getline(in, 256, ';');
		_flm.day = StrToInt(in);
		_in.getline(in, 256, ';');
		_flm.month = StrToInt(in);
		_in.getline(in, 256, ';');
		_flm.year = StrToInt(in);
		_in.getline(in, 256, '\n');
		_flm.box_office = StrToInt(in);
	}
	return _in;
}

void FilmLib::ProverkaVvodaRus(const string& _str) // ��� �������� ����� ������������� ���� �������� �������� ��� ����, ���������� ����������� ����������
{
	for (int i = 0; i < _str.length(); ++i)
	{
		if ((_str[i] > 32 && _str[i] < 48) || _str[i] > 57)
			throw 1; // ����������� ���������� ��� ������ ����� ������� ����
	}

}
