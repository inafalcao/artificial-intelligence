/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
import java.util.ArrayList;
import java.util.List;


public class Tabuleiro {
    
    public static int TAMANHO_TABULEIRO = 4;
    
    List<List<Integer>> tabuleiro;
    
    public Tabuleiro() {
        tabuleiro = new ArrayList<List<Integer>>(TAMANHO_TABULEIRO);

        for(int i = 0; i < TAMANHO_TABULEIRO; i++) {
            tabuleiro.add(i, new ArrayList<Integer>(TAMANHO_TABULEIRO));
            for(int j = 0; j < TAMANHO_TABULEIRO; j++) {
                tabuleiro.get(i).add(j, 0);
            }
        }
        
         tabuleiro.get(0).set(1, 1);
         tabuleiro.get(1).set(1, 1);
         
    }
    
    public int contarConflitos(int linha, int coluna) {
        int conflitos = contarConflitosLinha(linha, coluna) + 
                        contarConflitosColuna(linha, coluna) + 
                        contarConflitosDiagonal(linha, coluna);
        
        return conflitos;
    }
    
    public int contarConflitosLinha(int linha, int coluna) {
        int conflitos = 0;
        for(int i = 0; i < TAMANHO_TABULEIRO; i++) {
            if(i!=coluna && tabuleiro.get(linha).get(i) == 1)
                conflitos++;
        }
        
        return conflitos;
    }
    
    public int contarConflitosColuna(int linha, int coluna) {
        int conflitos = 0;
        for(int i = 0; i < TAMANHO_TABULEIRO; i++) {
            if(i!=linha && tabuleiro.get(coluna).get(i) == 1)
                conflitos++;
        }
        
        return conflitos;
    }
    
    public int contarConflitosDiagonal(int linha, int coluna) {
        int conflitos = 0;
        for(int i = 0; i < TAMANHO_TABULEIRO; i++) {
            for(int j = 0; j < TAMANHO_TABULEIRO; j++) {
                if(i!=linha && j!=coluna && tabuleiro.get(i).get(j) == 1)
                    conflitos++;
            }
        }
        
        return conflitos;
    }
    
    public void printTabuleiro() {
        for(int i = 0; i < TAMANHO_TABULEIRO; i++) {
            for(int j = 0; j < TAMANHO_TABULEIRO; j++) {
                System.out.print(tabuleiro.get(i).get(j) + " ");
                
            }
            System.out.print("\n");
        }
    }
    
}
