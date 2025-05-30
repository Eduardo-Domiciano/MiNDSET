/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Main.java to edit this template
 */
package unid5code2;

import javax.swing.JOptionPane;
/**
 *
 * @author DuDS
 */
public class Unid5code2 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
        int x;
        String resp;
        
        resp = JOptionPane.showInputDialog("Digite um valor inteiro para X");
        x = Integer.parseInt (resp);
        
        JOptionPane.showMessageDialog(null, "O valor digitado foi: " + x);
    }
    
}
