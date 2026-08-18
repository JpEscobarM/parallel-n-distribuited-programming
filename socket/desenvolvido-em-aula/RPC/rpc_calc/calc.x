struct args{
	float op1;
	float op2;
};

program calcprogram{
	version calcversion{
		float soma (struct args)=1;
		float subtracao(struct args)=2;
		float divisao (struct args)=3;
		float multiplicacao(struct args)=4;
	}=1;
}=0x21000000;
