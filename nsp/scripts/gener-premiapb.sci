P = premia_create();
P.set_asset[str="equity"];
P.set_model[str="BlackScholesndim"];

// les options sont r�parties en famille
// premia_get_family (famille, model) renvoie les options de la famille qui
// existe dans le mod�le
P.set_option[8, 3];

// premia_get_methods (famille, option, mod�le) renvoie la liste des m�thodes
// utilisables
P.set_method[1] // MC_LongstaffSchwatrz_ND

p_opt = P.get_option_values[];

p_opt(2)(3) = 2; // met la mautirt� � 2
p_opt(3)(3) = 120; // met le strike mautirt� � 120

P.set_option_values[p_opt]; // utilise la liste p_opt pour d�finir les
                            // param�tres de l'option

// les m�mes fonctions existent avec model et method � la place d'option

save('pipo',P); // sauve le pb dans pipo
