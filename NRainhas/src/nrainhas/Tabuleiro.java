package nrainhas;
/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

/**
 * Classe que armazena um tabuleiro, gera seu estado aleatório inicial,
 * conta quantidade de conflitos e move rainhas aleatoriamente.
 *
 * @author inafalcao
 *
 */
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
        
         //tabuleiro.get(0).set(1, 1);
         //tabuleiro.get(1).set(1, 1);
         
    }
    
    public int contarTodosOsConflitos() {
    	int contagem = 0;
    	
    	for(int coluna = 0; coluna < TAMANHO_TABULEIRO; coluna++) {
    		contagem += contarConflitos(linhaDaRainha(coluna), coluna);
    	}
    	
    	return contagem/2;
    }
    
    /**
     * Conta todos os conflitos de uma determinada rainha.
     * @param linha
     * @param coluna
     * @return número de conflitos com essa rainha
     */
    public int contarConflitos(int linha, int coluna) {
        int conflitos = contarConflitosLinha(linha, coluna) + 
                        contarConflitosColuna(linha, coluna) + 
                        contarConflitosDiagonal(linha, coluna);
        
        return conflitos;
    }
    
    private int contarConflitosLinha(int linha, int coluna) {
        int conflitos = 0;
        for(int i = 0; i < TAMANHO_TABULEIRO; i++) {
            if(i!=coluna && tabuleiro.get(linha).get(i) == 1)
                conflitos++;
        }
        
        return conflitos;
    }
    
    private int contarConflitosColuna(int linha, int coluna) {
        int conflitos = 0;
        for(int i = 0; i < TAMANHO_TABULEIRO; i++) {
            if(i!=linha && tabuleiro.get(coluna).get(i) == 1)
                conflitos++;
        }
        
        return conflitos;
    }
    
    private int contarConflitosDiagonal(int linha, int coluna) {
        int conflitos = 0;
        for(int i = 0; i < TAMANHO_TABULEIRO; i++) {
            for(int j = 0; j < TAMANHO_TABULEIRO; j++) {
                if(i!=linha && j!=coluna && tabuleiro.get(i).get(j) == 1)
                    conflitos++;
            }
        }
        
        return conflitos;
    }
    
    /**
     * Posicionamento inicial das rainhas no tabuleiro.
     * Posiciona as N rainhas aleatoriamente em cada coluna.
     * 
     * Para isto são feitos os seguintes passos:
     * 1. Seleciona coluna
     * 2. Seleciona posição aleatória na coluna e coloca a rainha nesta posição.
     */
    public void posicionarRainhasIniciais() {
    	Random gerador = new Random();
        int linha = 0;
    	
        for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        	// Random linha da coluna i
        	linha = gerador.nextInt(TAMANHO_TABULEIRO);
        	tabuleiro.get(linha).set(i, 1);
		}
    }
    
    /**
     * Move aleatoriamente uma rainha.
     * 
     * Para isto são feitos os seguintes passos:
     * 1. Escolho uma coluna aleatoriamente
     * 2. Movo uma rainha aleatoriamente apenas nessa coluna
     */
    public void geraProximoEstadoAleatoriamente() {
    	Random gerador = new Random();
    	int linha = 0;
    	int coluna = 0;
    	
    	coluna = gerador.nextInt(TAMANHO_TABULEIRO);
    	int linhaDaRainha = linhaDaRainha(coluna);
    	
    	boolean mudouRainhaDeLugar = false;
    	
    	while(!mudouRainhaDeLugar) {
    		
    		linha = gerador.nextInt(TAMANHO_TABULEIRO);
    		
    		if(linha != linhaDaRainha) {
    			tabuleiro.get(linhaDaRainha).set(coluna, 0);
    			tabuleiro.get(linha).set(coluna, 1);
    			mudouRainhaDeLugar = true;
    		}
    	}
    	
    }
    
    private int linhaDaRainha(int coluna) {
    	for(int i = 0; i < TAMANHO_TABULEIRO; i++) {
    		if(tabuleiro.get(i).get(coluna) == 1)
    			return i;
    	}
    	return -1;
    }
    
    public void printTabuleiro() {
        for(int i = 0; i < TAMANHO_TABULEIRO; i++) {
            for(int j = 0; j < TAMANHO_TABULEIRO; j++) {
                System.out.print(tabuleiro.get(i).get(j) + " ");
            }
            System.out.print("\n");
        }
        System.out.print("\n");
    }
    
}
