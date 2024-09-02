/**
 * Registry
 */
public class Registry {

	public static Integer staticID = 0;
	private Integer id;
	private String name;
	private String lastName;

	public Registry(){
		this.id = staticID++;
	}

	public Registry(String name, String lastName) {
		this();
		this.name = name;
		this.lastName = lastName;
	}

	public Integer GetId() {
		return id;
	}
	public String GetName() {
		return name;
	}
	public String GetLastName() {
		return lastName;
	}
	
}