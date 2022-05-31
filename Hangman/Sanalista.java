import java.io.*;
import java.util.*;

public class Sanalista {
	private List<String> sanat;
	
	public Sanalista(String filename){
		this.sanat = new ArrayList<String>();
		
		try {
			BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(filename), "utf-8"));
			String line;
			
			line = br.readLine();
			while(line != null){
				this.sanat.add(line);
				line = br.readLine();
			};
			
			br.close();
			
		} catch (IOException e) {
			e.printStackTrace();
			System.exit(0);
		}
	}
	
	public Sanalista(List<String> sanat){
		this.sanat = sanat;
	}
	
	public List<String> annaSanat(){
		return sanat;
	}
	
	public Sanalista sanatJoidenPituusOn(int pituus){
		List<String> filteredList = new ArrayList<String>();
		for(String sana : this.sanat){
			if(sana.length() == pituus)
				filteredList.add(sana);
		}
		
		return new Sanalista(filteredList);
	}
	
	public Sanalista sanaJoissaMerkit(String mjono){
		List<String> filteredList = new ArrayList<String>();
		
		for(String sana : this.sanat){
			if(sana.length() != mjono.length()) 
				continue;
			
			for(int i = 0; i < mjono.length(); i++){
				if(mjono.charAt(i) != '_'){
					if(mjono.charAt(i) != sana.charAt(i)){
						break;
					}
				}
				if(i == mjono.length()-1)
					filteredList.add(sana);
			}	
		}
		
		return new Sanalista(filteredList);
	}
}