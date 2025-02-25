
void inserirDesconto(float *preco, float desconto) {
    *preco -= (*preco * (desconto / 100));
}

int main() {
    float preco, desconto;
    
    
    printf("Digite o preco do produto: ");
    scanf("%f", &preco);
    
   
    printf("Digite o percentual de desconto: ");
    scanf("%f", &desconto);
    
    printf("Preco original: R$ %.2f\n", preco);
    

    inserirDesconto(&preco, desconto);
    
    printf("Desconto aplicado: %.2f%%\n", desconto);
    printf("Preco final apos o desconto: R$ %.2f\n", preco);
    
    return 0;
}
