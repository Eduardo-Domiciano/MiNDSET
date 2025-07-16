import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.text.DecimalFormat;




public class Calculadora_de_IMC extends JFrame {

    private JTextField campoPeso;
    private JTextField campoAltura;

    private JLabel labelResultadoIMC;
    private JLabel labelClasificacao;

    public Calculadora_de_IMC() {

            // Configuracao da janelaa
            setTitle("Calculadora de IMC");
            setSize(600, 250);
            setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            setLocationRelativeTo(null);
            setLayout(new GridLayout(5, 2, 10, 10)); 



        //
        // Componente da interface

        JLabel labelPeso = new JLabel("Peso (kg): ");
        campoPeso = new JTextField();
        JLabel labelAltura = new JLabel("Altura (Valor em centimetros):");
        campoAltura = new JTextField();

        JButton botaoCalcular = new JButton("-Calcular IMC-");

        JLabel labelTextoIMC = new JLabel("Seu IMC: ");
        labelResultadoIMC = new JLabel(""); 

        JLabel labelTextoClassificacao = new JLabel("Classificação:");
        labelClasificacao = new JLabel("");

        // Adiciona os componentes à janela
        add(labelPeso);
        add(campoPeso);
        add(labelAltura);
        add(campoAltura);
        add(botaoCalcular);
        //
        add(new JLabel());
        add(labelTextoIMC);
        add(labelResultadoIMC);
        add(labelTextoClassificacao);
        add(labelClasificacao);



          // calcula
        botaoCalcular.addActionListener(new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    calcularIMC();
                }
        });
    }
    private void calcularIMC() {
            try {
                double peso = Double.parseDouble(campoPeso.getText().replace(",", "."));
                double alturaCm = Double.parseDouble(campoAltura.getText().replace(",", "."));

                if (alturaCm <= 0 || peso <= 0) {
                    JOptionPane.showMessageDialog(this,
                            "Peso e altura tem que ser valor positivo.",
                            "Erro de Entrada",
                            JOptionPane.ERROR_MESSAGE);
                    labelResultadoIMC.setText("");
                    labelClasificacao.setText("");
                    return;
                }
                // aqui converte para metros pra poder calcular
                double alturaM = alturaCm / 100.0;

                double imc = peso / (alturaM * alturaM);
                DecimalFormat df = new DecimalFormat("#.##");
                labelResultadoIMC.setText(df.format(imc));
                classificarIMC(imc);

            } catch (NumberFormatException ex) {
                JOptionPane.showMessageDialog(this,
                        "Valores inseridos invalidos. Confira os valores inseridos",
                        "Erro de Formato",
                        JOptionPane.ERROR_MESSAGE);
                labelResultadoIMC.setText("");
                labelClasificacao.setText("");
            }
    }

    private void classificarIMC(double imc) {
            String classificacao;
            if (imc < 18.5) {
                classificacao = "Abaixo do peso";
            } else if (imc < 24.9) {
                classificacao = "Peso normal";
            } else if (imc < 29.9) {
                classificacao = "Sobrepeso";
            } else if (imc < 34.9) {
                classificacao = "Obesidade Grau I";
            } else if (imc < 39.9) {
                classificacao = "Obesidade Grau II";
            } else if (imc > 39.9) {
                classificacao = "Obesidade Gru III";
            } else {
                System.err.println(classificacao = "Erro no calculo. Contate o suporte!");
            }
            labelClasificacao.setText(classificacao);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {

            @Override
            public void run() {
                new Calculadora_de_IMC().setVisible(true);
            }
        });
    }
}