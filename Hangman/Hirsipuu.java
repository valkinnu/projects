import java.util.List;
import java.util.Random;


public class Hirsipuu {
	private String sana;
	private int arvaustenMaksimiMaara;
	private int arvaustenMaara;
	private List<Character> arvatutKirjaimet;
	private char[] avatutKirjaimet;
	
	public Hirsipuu(Sanalista sanalista, int arvaustenMaara){
		this.arvaustenMaksimiMaara = arvaustenMaara;
		this.arvaustenMaara = 0;
		
		Random random = new Random();
		List<String> sanat = sanalista.annaSanat();
		this.sana = sanat.get(random.nextInt(sanat.size()));
		this.avatutKirjaimet = new char[this.sana.length()];
		
		for(int i = 0; i < this.sana.length(); i++){
			if(this.sana.charAt(i) == '-'){
				this.avatutKirjaimet[i] = '-';
			}else{
				this.avatutKirjaimet[i] = '*';
			}
		}
	}
	
	public boolean arvaa(Character merkki){
		boolean onnistunut = false;
		for(int i = 0; i < avatutKirjaimet.length; i++){
			if(sana.charAt(i) == (char)Character.toLowerCase(merkki)){
				avatutKirjaimet[i] = merkki;
				onnistunut = true;
			}
		}
		
		if(!onnistunut)
			arvaustenMaara++;
		
		return onnistunut;
	}
	
	public List<Character> arvaukset(){
		return arvatutKirjaimet;
	}
	
	public int arvauksiaOnJaljella(){
		return arvaustenMaksimiMaara - arvaustenMaara;
	}
	
	public String sana(){
		return this.sana;
	}
	
	public boolean onLoppu(){
		for(int i = 0; i < this.avatutKirjaimet.length; i++){
			if(this.avatutKirjaimet[i] == '*')
				return false;
		}
		return true;
	}

	public int getArvaustenMaara() {
		return this.arvaustenMaksimiMaara;
	}

	public void setArvaustenMaara(int arvaustenMaara) {
		this.arvaustenMaksimiMaara = arvaustenMaara;
	}

	public char[] getAvatutKirjaimet() {
		return avatutKirjaimet;
	}

	public void setAvatutKirjaimet(char[] avatutKirjaimet) {
		this.avatutKirjaimet = avatutKirjaimet;
	}
}
