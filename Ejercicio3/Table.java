import java.util.Vector;

public class Table {
	
	Vector<Registry> Registries;

	public Table() {
		Registries = new Vector<Registry>();
	}

	public void AddRegistry(Registry registry) {
		Registries.add(registry);
	}

	/*
	 * This method searches for a registry by its id. It uses a binary search
	 */
	public Registry SearchRegistryById(Integer id) {
		if(Registries.size() == 0) { return null; }
		if(Registries.size() == 1 && Registries.get(0).GetId() == id) {
			return Registries.get(0);
		}

		Integer left = 0;
		Integer right = Registries.size() - 1;

		while (left <= right) {
			Integer middle = left + (right - left) / 2;

			if (Registries.get(middle).GetId() == id) {
				return Registries.get(middle);
			}

			if (Registries.get(middle).GetId() < id) {
				left = middle + 1;
			} else {
				right = middle - 1;
			}
		}

		return null;
	}

	public Registry LinearSearch(Integer ID){
		for (Registry registry : Registries) {
			if(registry.GetId() == ID){
				return registry;
			}
		}
		return null;
	}
}
