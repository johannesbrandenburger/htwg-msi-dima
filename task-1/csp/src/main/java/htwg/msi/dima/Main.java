package htwg.msi.dima;
import org.chocosolver.solver.Model;
import org.chocosolver.solver.variables.BoolVar;


public class Main {
    public static void main(String[] args) {

        Model model = new Model("Diner Planning");
        
        // define variables for all members of the family
        BoolVar Wife = model.boolVar("Wife");
        BoolVar Husband = model.boolVar("Husband");
        BoolVar Emma = model.boolVar("Emma");
        BoolVar Georg = model.boolVar("Georg");
        BoolVar Ivana = model.boolVar("Ivana");

        // extract the constraints from the text (think)
        // H -> W
        // I or G
        // W xor E
        // E <-> G
        // I -> (G and H)

        // define constraints
        Husband.imp(Wife).post();
        Ivana.or(Georg).post();
        Wife.xor(Emma).post();
        Emma.eq(Georg).post();
        Ivana.imp(Georg.and(Husband)).post();

        // solve and print solution
        model.getSolver().solve();
        System.out.println("Wife: " + Wife.getValue());         // false
        System.out.println("Husband: " + Husband.getValue());   // false
        System.out.println("Emma: " + Emma.getValue());         // true
        System.out.println("Georg: " + Georg.getValue());       // true
        System.out.println("Ivana: " + Ivana.getValue());       // false
    }
}
