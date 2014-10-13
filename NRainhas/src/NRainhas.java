/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

import java.util.ArrayList;
import java.util.List;

/**
 *
 * @author 344079
 */
public class NRainhas {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {

        Tabuleiro tab = new Tabuleiro();
        tab.printTabuleiro();
        System.out.print(tab.contarConflitos(0, 1));

    }
}
