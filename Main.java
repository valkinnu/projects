public class Main {
	
	public static void main(String[] args){
		
		String filename = "sanalista.txt";
		int arvaustenMaara = 8;
		
		if(args.length != 0){
			filename = args[0];
			
			if(args.length != 1){
				try{
					arvaustenMaara = Integer.parseInt(args[1]);
					if(arvaustenMaara <= 0){
						System.out.println("Arvausten määrä pitää olla positiivinen kokonaisluku");
						System.exit(0);
					}
				}catch(NumberFormatException e){
					System.out.println("Arvausten määrä pitää olla positiivinen kokonaisluku");
					System.exit(0);
				}
			}
		}
		
		Sanalista sanalista = new Sanalista(filename);
		Hirsipuu hirsipuu = new Hirsipuu(sanalista, arvaustenMaara);
		
		GUI gui = new GUI(hirsipuu);
		gui.initialisoi();
	}
}
