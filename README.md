# Algoritmo One Shot Timer para Raspberry Pi Pico W

## 📌 Descrição
Este programa implementa um **sistema de controle com one-shot timer**, onde, ao pressionar um botão, inicia-se uma **sequência de desligamento dos LEDs**. Cada LED apaga após um determinado intervalo de tempo. O botão **só poderá ser acionado novamente após os três LEDs estarem completamente apagados**, garantindo que não haja interrupções no ciclo de temporização.

## 🔧 Materiais Utilizados
- 1 × Raspberry Pi Pico W
- 3 × LEDs coloridos (Azul, Vermelho e Verde)
- 3 × Resistores de 330 ohms
- 1 × Simulador Wokwi

## 🛠 Instalação e Uso
1. Clone este repositório para o seu Raspberry Pi Pico W:
   ```sh
   git clone https://github.com/engleonardorodrigues/one-shot-timer-RP2040.git
   ```
2. Compile e carregue o código no Raspberry Pi Pico W utilizando o SDK do **Pico**.
3. Conecte os LEDs e o botão conforme especificado no código.
4. Execute o programa e pressione o botão para iniciar a sequência de temporização dos LEDs.

## ⚙️ Funcionamento
- Quando o botão é pressionado, **todos os LEDs acendem simultaneamente**.
- Após **3 segundos**, o **LED azul** apaga.
- Após mais **3 segundos**, o **LED vermelho** apaga.
- Após mais **3 segundos**, o **LED verde** apaga.
- O botão só poderá ser pressionado novamente **depois que todos os LEDs estiverem apagados**.

## 📜 Código Fonte
O código fonte está implementado em **C** e utiliza o SDK do **Pico** para manipulação dos pinos GPIO e temporizadores.

## 🖥 Simulação no Wokwi (Vídeo Demonstrativo)
Este projeto pode ser testado no simulador online **Wokwi**. Basta clicar no link a seguir para assistir ao vídeo demonstrativo.

[Vídeo Demonstrativo](https://www.youtube.com/watch?v=Odi_st8Awek)

## 📜 Licença
Este projeto está licenciado sob a **MIT License** - sinta-se livre para modificá-lo e distribuí-lo conforme necessário.

## 📩 Contato
Caso tenha dúvidas ou sugestões, entre em contato:
- **Desenvolvedor**: Leonardo Rodrigues
- **Linkedin**: https://www.linkedin.com/in/leonardorodrigues7/
