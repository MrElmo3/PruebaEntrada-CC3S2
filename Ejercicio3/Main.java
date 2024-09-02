
public class Main {
	
	public static void main(String[] args) {
		
		Table table = new Table();
		//Nota: si tiene errores aqui, es el intellisense, el codigo si funciona :D
		for (int i = 0; i < 100; i++) {
			Registry registry = new Registry("Name" + i, "LastName" + i);
			table.AddRegistry(registry);
		}
		
		double start = System.currentTimeMillis();
		Registry registry = table.SearchRegistryById(43);
		double end = System.currentTimeMillis();
		System.out.println("Binary search time: " + (end - start) + "ms");

		start = System.currentTimeMillis();
		registry = table.LinearSearch(43);
		end = System.currentTimeMillis();
		System.out.println("Linear search time: " + (end - start) + "ms");

	}

}
