import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.*;

public class GUI {
	private Hirsipuu hirsipuu;
	private JPanel panel;
	private JTextArea arvattuTeksti;
	private JProgressBar tuhoEsitin;

	public GUI(Hirsipuu hirsipuu) {
		this.hirsipuu = hirsipuu;
	}

	public void initialisoi() {
		JFrame frame = new JFrame();

		panel = new JPanel();
		panel.setBackground(Color.WHITE);

		final String kirjaimet = "ABCDEFGHIJKLMNOPQRSTUVWXYZÄÖ";

		for (int i = 0; i < kirjaimet.length(); i++) {
			JButton kirjain = new JButton("" + kirjaimet.charAt(i));
			kirjain.setPreferredSize(new Dimension(50, 50));
			kirjain.setFont(new Font("Arial", Font.BOLD, 14));
			kirjain.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					JButton source = (JButton) e.getSource();
					boolean onnistunut = hirsipuu.arvaa(source.getText()
							.charAt(0));
					source.setEnabled(false);

					if (onnistunut)
						source.setBackground(Color.GREEN);
					else
						source.setBackground(Color.RED);

					paivita();
				}
			});
			panel.add(kirjain);
		}

		arvattuTeksti = new JTextArea(String.valueOf(hirsipuu
				.getAvatutKirjaimet()));
		arvattuTeksti.setFont(new Font("Arial", Font.PLAIN, 40));
		panel.add(arvattuTeksti);

		tuhoEsitin = new JProgressBar();
		tuhoEsitin.setPreferredSize(new Dimension(400, 30));
		tuhoEsitin.setStringPainted(true);
		tuhoEsitin.setForeground(Color.RED);
		tuhoEsitin.setValue(100);
		tuhoEsitin.setString("Arvauksia jäljellä: "
				+ hirsipuu.arvauksiaOnJaljella());
		panel.add(tuhoEsitin);

		frame.add(panel);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(450, 400);
		frame.setVisible(true);
	}

	public void paivita() {
		arvattuTeksti.setText(String.valueOf(hirsipuu.getAvatutKirjaimet()));
		tuhoEsitin.setValue((int) ((float) hirsipuu.arvauksiaOnJaljella()
				/ hirsipuu.getArvaustenMaara() * 100));
		tuhoEsitin.setString("Arvauksia jäljellä: " + hirsipuu.arvauksiaOnJaljella());

		if (hirsipuu.onLoppu()) {
			JOptionPane.showMessageDialog(panel, "VOITIT PELIN");
			for (Component component : panel.getComponents()) {
				component.setEnabled(false);
			}
		}

		if (hirsipuu.arvauksiaOnJaljella() <= 0) {
			arvattuTeksti.setText(hirsipuu.sana().toUpperCase());
			JOptionPane.showMessageDialog(panel, "HÄVISIT PELIN");
			for (Component component : panel.getComponents()) {
				component.setEnabled(false);
			}
		}
	}
}
