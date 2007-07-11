typedef struct Buffer {
public:
	int **buff;// - указатель
	long len_buff;// - длина динамического массива
	long frequency;// частота выборки
public:
	Buffer(int **buffer, long len_buff, long frequency){
		this->buff = buff;
		this->len_buff = len_buff;
		this->frequency = frequency;
	}
	Buffer(){
		Buffer(NULL, 0, 0);
	}
};