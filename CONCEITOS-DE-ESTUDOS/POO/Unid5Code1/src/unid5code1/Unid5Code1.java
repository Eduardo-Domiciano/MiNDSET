/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package unid5code1;

/**
 *
 * @author DuDS
 */
public class Unid5Code1 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Empregado func = new Empregado();
        
        func.nome = "Jose";
        func.sobrenome = "Maria";
        func.matricula = 358;
        func.salario = 2234.54f;
        
        System.out.println("Nome do funcionario: " + func.nome + " " + func.sobrenome);
        System.out.println("Numero matricula: " + func.matricula);
        System.out.println("Salário: RS " + func.salario);
    }
    
}
