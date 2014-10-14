package nrainhas;

/**
 *
 * @author inafalcao
 */
public class NRainhas {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {

        Tabuleiro tab = new Tabuleiro();
        tab.posicionarRainhasIniciais();
        tab.printTabuleiro();
        tab.geraProximoEstadoAleatoriamente();
        tab.printTabuleiro();
        //System.out.print(tab.contarConflitos(0, 1));

    }
}
