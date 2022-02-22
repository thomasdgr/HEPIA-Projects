CREATE SCHEMA IF NOT EXISTS `mcdo` DEFAULT CHARACTER SET utf8;
USE `mcdo`;


-- creation de la table Article
CREATE TABLE IF NOT EXISTS `mcdo`.`Article`(
    `nom` VARCHAR(127) NOT NULL,
    `prix` DECIMAL(10,2) UNSIGNED NOT NULL DEFAULT 0,
    PRIMARY KEY(`nom`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- creation de la table PlatPrincipal
CREATE TABLE IF NOT EXISTS `mcdo`.`PlatPrincipal`(
    `nom_article` VARCHAR(127) NOT NULL,
    PRIMARY KEY(`nom_article`),
    CONSTRAINT `contrainte_plat_article`
        FOREIGN KEY(`nom_article`) REFERENCES `mcdo`.`Article` (`nom`)
        ON DELETE CASCADE
        ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- creation de la table Boisson
CREATE TABLE IF NOT EXISTS `mcdo`.`Boisson`(
    `nom_article` VARCHAR(127) NOT NULL,
    PRIMARY KEY(`nom_article`),
    CONSTRAINT `contrainte_boisson_article`
        FOREIGN KEY(`nom_article`) REFERENCES `mcdo`.`Article` (`nom`)
        ON DELETE CASCADE
        ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- creation de la table Accompagnement
CREATE TABLE IF NOT EXISTS `mcdo`.`Accompagnement`(
    `nom_article` VARCHAR(127) NOT NULL,
    PRIMARY KEY(`nom_article`),
    CONSTRAINT `contrainte_accompagnement_article`
        FOREIGN KEY(`nom_article`) REFERENCES `mcdo`.`Article` (`nom`)
        ON DELETE CASCADE
        ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- creation de la table Menu
CREATE TABLE IF NOT EXISTS `mcdo`.`Menu`(
    `id_menu` INT UNSIGNED NOT NULL DEFAULT 0,
    `nom` VARCHAR(127) NOT NULL,
    `plat` VARCHAR(127) NOT NULL,
    `boisson` VARCHAR(127) NOT NULL,
    `accompagnement` VARCHAR(127) NOT NULL,
    PRIMARY KEY (`id_menu`),
    CONSTRAINT `contrainte_menu_plat`
        FOREIGN KEY(`plat`) REFERENCES `mcdo`.`PlatPrincipal` (`nom_article`)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    CONSTRAINT `contrainte_menu_boisson`
        FOREIGN KEY(`boisson`) REFERENCES `mcdo`.`Boisson` (`nom_article`)
        ON DELETE CASCADE
        ON UPDATE CASCADE,
    CONSTRAINT `contrainte_menu_accompagnement`
        FOREIGN KEY(`accompagnement`) REFERENCES `mcdo`.`Accompagnement` (`nom_article`)
        ON DELETE CASCADE
        ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- creation de la table Commande
CREATE TABLE IF NOT EXISTS `mcdo`.`Commande`(
    `no_commande` INT UNSIGNED AUTO_INCREMENT NOT NULL,
    `nom` VARCHAR(127) NOT NULL,
    `prenom` VARCHAR(127) NOT NULL,
    PRIMARY KEY(`no_commande`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- creation de la table CommandeMenu
CREATE TABLE IF NOT EXISTS `mcdo`.`CommandeMenu`(
    `id_menu` INT UNSIGNED NOT NULL DEFAULT 0,
    `no_commande` INT UNSIGNED NOT NULL DEFAULT 0,
    `quantite` INT UNSIGNED NOT NULL DEFAULT 1,
    PRIMARY KEY(`id_menu`, `no_commande`),
    CONSTRAINT `contrainte_commandeMenu_commande`
        FOREIGN KEY(`no_commande`) REFERENCES `mcdo`.`Commande` (`no_commande`)
        ON DELETE NO ACTION  -- on ne veut pouvoir ni supprimer 
        ON UPDATE NO ACTION, -- ni modifier une commande
    CONSTRAINT `contrainte_commandeMenu_menu`
        FOREIGN KEY(`id_menu`) REFERENCES `mcdo`.`Menu` (`id_menu`)
        ON DELETE NO ACTION
        -- ON DELETE ... on aimerait que id_menu reste le nom du menu même si le menu a été suprimé
        -- on voudrait garder un trace du contenu de la commande même si certains éléments ont été supprimé depuis
        ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- creation de la table CommandeArticle
CREATE TABLE IF NOT EXISTS `mcdo`.`CommandeArticle`(
    `nom_article` VARCHAR(127) NOT NULL,
    `no_commande` INT UNSIGNED NOT NULL DEFAULT 0,
    `quantite` INT UNSIGNED NOT NULL DEFAULT 1,
    PRIMARY KEY(`nom_article`, `no_commande`),
    CONSTRAINT `contrainte_commandeArticle_commande`
    FOREIGN KEY(`no_commande`) REFERENCES `mcdo`.`Commande` (`no_commande`)
        ON DELETE NO ACTION
        ON UPDATE NO ACTION, -- on ne veut pas supprimer ou update une commande
    CONSTRAINT `contrainte_commandeArticle_article`
    FOREIGN KEY(`nom_article`) REFERENCES `mcdo`.`Article` (`nom`)
    ON DELETE NO ACTION  -- on aimerait que nom_article reste le nom du de l'article même si l'article a été supprimé
    ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;


-- PROCEDURES

-- Procédure qui affiche le prix d'un article
DELIMITER $
CREATE PROCEDURE mcdo.getArticlePrice(nom_article VARCHAR(127))
BEGIN
    SELECT prix FROM Article WHERE nom = nom_article;
END$
DELIMITER ;

-- Procédure qui calcule le prix d'un menu en fonction de son id
DELIMITER //
CREATE PROCEDURE mcdo.totalPriceMenu(IN id_menu_wanted INT UNSIGNED)
BEGIN
    SELECT SUM(prix) FROM (
          (SELECT Article.prix FROM Menu INNER JOIN Boisson ON Menu.boisson = Boisson.nom_article INNER JOIN Article ON Boisson.nom_article = Article.nom WHERE Menu.id_menu = id_menu_wanted) 
    UNION ALL (SELECT Article.prix FROM Menu INNER JOIN PlatPrincipal ON  Menu.plat = PlatPrincipal.nom_article INNER JOIN Article ON PlatPrincipal.nom_article = Article.nom WHERE Menu.id_menu = id_menu_wanted) 
    UNION ALL (SELECT Article.prix FROM Menu INNER JOIN Accompagnement ON  Menu.accompagnement = Accompagnement.nom_article INNER JOIN Article ON Accompagnement.nom_article = Article.nom WHERE Menu.id_menu = id_menu_wanted)
    ) AS totalPrice;
END//
DELIMITER ;

-- VUES 

-- Vue qui montre le prix total en fonction d'un menu
CREATE VIEW infoMenu AS
SELECT id_menu, SUM(prix) AS prixMenu, nom FROM(
(SELECT id_menu, Menu.nom, prix FROM Menu INNER JOIN Boisson ON Menu.boisson = Boisson.nom_article INNER JOIN Article ON Boisson.nom_article = Article.nom) 
UNION ALL
(SELECT id_menu, Menu.nom, prix FROM Menu INNER JOIN PlatPrincipal ON Menu.plat = PlatPrincipal.nom_article INNER JOIN Article ON PlatPrincipal.nom_article = Article.nom )
UNION ALL
(SELECT id_menu, Menu.nom, prix FROM Menu INNER JOIN Accompagnement ON Menu.accompagnement = Accompagnement.nom_article INNER JOIN Article ON Accompagnement.nom_article = Article.nom)
) AS allMenu GROUP BY id_menu, nom;

-- Vue qui montre les commandes composées d'au moins un menu ET un article
CREATE VIEW CommandWithMinOneMenuAndArticle AS
SELECT  Commande.no_commande, Commande.nom, Commande.prenom, Menu.nom AS nom_menu, CommandeArticle.nom_article FROM Commande 
INNER JOIN CommandeMenu ON Commande.no_commande = CommandeMenu.no_commande 
INNER JOIN CommandeArticle ON Commande.no_commande = CommandeArticle.no_commande INNER JOIN Menu on CommandeMenu.id_menu = Menu.id_menu;


DELIMITER $
CREATE TRIGGER trigger_prix BEFORE INSERT ON Article
FOR EACH ROW
BEGIN
    IF new.prix > 15.0
    THEN 
        signal sqlstate '45000'
        set message_text = 'Le prix d''un article doit etre compris entre 0.- et 15.-';
    END IF;
END;
$
DELIMITER ;


-- POPULATE

-- ARTICLES
START TRANSACTION;
USE `mcdo`;
-- plats burgers
INSERT INTO `mcdo`.`Article` (`nom`, `prix`) VALUES ('big mac', 3.80);
INSERT INTO `mcdo`.`Article` (`nom`, `prix`) VALUES ('mc chicken', 3.70);
INSERT INTO `mcdo`.`Article` (`nom`, `prix`) VALUES ('mc first', 1.20);
INSERT INTO `mcdo`.`Article` (`nom`, `prix`) VALUES ('royal bacon', 4.0);
INSERT INTO `mcdo`.`Article` (`nom`, `prix`) VALUES ('royal cheese', 3.70);
INSERT INTO `mcdo`.`Article` (`nom`, `prix`) VALUES ('royal deluxe', 3.80);
INSERT INTO `mcdo`.`Article` (`nom`, `prix`) VALUES ('filet-o-fish', 3.80);
INSERT INTO `mcdo`.`Article` (`nom`, `prix`) VALUES ('double cheese', 2.60);
INSERT INTO `mcdo`.`Article` (`nom`, `prix`) VALUES ('triple cheese', 2.70);
INSERT INTO `mcdo`.`Article` (`nom`, `prix`) VALUES ('cbo', 4.70);
-- plats autres
INSERT INTO `mcdo`.`Article` (`nom`, `prix`) VALUES ('mc wrap poulet bacon', 4.80);
INSERT INTO `mcdo`.`Article` (`nom`, `prix`) VALUES ('nuggets x20', 6.30);
INSERT INTO `mcdo`.`Article` (`nom`, `prix`) VALUES ('salade caesar', 6.30);
-- accompagnements
INSERT INTO `mcdo`.`Article` (`nom`, `prix`) VALUES ('hamburger', 1.20);
INSERT INTO `mcdo`.`Article` (`nom`, `prix`) VALUES ('cheeseburger', 1.60);
INSERT INTO `mcdo`.`Article` (`nom`, `prix`) VALUES ('nuggets x4', 2.70);
INSERT INTO `mcdo`.`Article` (`nom`, `prix`) VALUES ('nuggets x6', 3.70);
INSERT INTO `mcdo`.`Article` (`nom`, `prix`) VALUES ('nuggets x9', 4.10);
INSERT INTO `mcdo`.`Article` (`nom`, `prix`) VALUES ('petites frites', 1.50);
INSERT INTO `mcdo`.`Article` (`nom`, `prix`) VALUES ('moyennes frites', 2.10);
INSERT INTO `mcdo`.`Article` (`nom`, `prix`) VALUES ('grandes frites', 2.60);
INSERT INTO `mcdo`.`Article` (`nom`, `prix`) VALUES ('petites potatoes', 1.50);
INSERT INTO `mcdo`.`Article` (`nom`, `prix`) VALUES ('moyennes potatoes', 2.10);
INSERT INTO `mcdo`.`Article` (`nom`, `prix`) VALUES ('grandes potatoes', 2.60);
-- boissons
INSERT INTO `mcdo`.`Article` (`nom`, `prix`) VALUES ('petit coca-cola', 1.60);
INSERT INTO `mcdo`.`Article` (`nom`, `prix`) VALUES ('moyen coca-cola', 2.10);
INSERT INTO `mcdo`.`Article` (`nom`, `prix`) VALUES ('grand coca-cola', 2.60);
INSERT INTO `mcdo`.`Article` (`nom`, `prix`) VALUES ('petit ice tea', 1.60);
INSERT INTO `mcdo`.`Article` (`nom`, `prix`) VALUES ('moyen ice tea', 2.10);
INSERT INTO `mcdo`.`Article` (`nom`, `prix`) VALUES ('grand ice tea', 2.60);
INSERT INTO `mcdo`.`Article` (`nom`, `prix`) VALUES ('petit fanta', 1.60);
INSERT INTO `mcdo`.`Article` (`nom`, `prix`) VALUES ('moyen fanta', 2.10);
INSERT INTO `mcdo`.`Article` (`nom`, `prix`) VALUES ('grand fanta', 2.60);
INSERT INTO `mcdo`.`Article` (`nom`, `prix`) VALUES ('evian 50cl', 2.00);
INSERT INTO `mcdo`.`Article` (`nom`, `prix`) VALUES ('badoit 50cl', 2.50);
INSERT INTO `mcdo`.`Article` (`nom`, `prix`) VALUES ('cafe', 1.40);
INSERT INTO `mcdo`.`Article` (`nom`, `prix`) VALUES ('cafe allonge', 1.50);
INSERT INTO `mcdo`.`Article` (`nom`, `prix`) VALUES ('the', 1.40);
INSERT INTO `mcdo`.`Article` (`nom`, `prix`) VALUES ('chocola chaud', 1.90);
COMMIT;

-- PLATS
START TRANSACTION;
USE `mcdo`;
-- plats burgers
INSERT INTO `mcdo`.`PlatPrincipal` (`nom_article`) VALUES ('big mac');
INSERT INTO `mcdo`.`PlatPrincipal` (`nom_article`) VALUES ('mc chicken');
INSERT INTO `mcdo`.`PlatPrincipal` (`nom_article`) VALUES ('mc first');
INSERT INTO `mcdo`.`PlatPrincipal` (`nom_article`) VALUES ('royal bacon');
INSERT INTO `mcdo`.`PlatPrincipal` (`nom_article`) VALUES ('royal cheese');
INSERT INTO `mcdo`.`PlatPrincipal` (`nom_article`) VALUES ('royal deluxe');
INSERT INTO `mcdo`.`PlatPrincipal` (`nom_article`) VALUES ('filet-o-fish');
INSERT INTO `mcdo`.`PlatPrincipal` (`nom_article`) VALUES ('double cheese');
INSERT INTO `mcdo`.`PlatPrincipal` (`nom_article`) VALUES ('triple cheese');
INSERT INTO `mcdo`.`PlatPrincipal` (`nom_article`) VALUES ('cbo');
-- plats autres
INSERT INTO `mcdo`.`PlatPrincipal` (`nom_article`) VALUES ('mc wrap poulet bacon');
INSERT INTO `mcdo`.`PlatPrincipal` (`nom_article`) VALUES ('nuggets x20');
INSERT INTO `mcdo`.`PlatPrincipal` (`nom_article`) VALUES ('salade caesar');
COMMIT;

-- ACCOMPAGNEMENTS
START TRANSACTION;
USE `mcdo`;
INSERT INTO `mcdo`.`Accompagnement` (`nom_article`) VALUES ('hamburger');
INSERT INTO `mcdo`.`Accompagnement` (`nom_article`) VALUES ('cheeseburger');
INSERT INTO `mcdo`.`Accompagnement` (`nom_article`) VALUES ('nuggets x4');
INSERT INTO `mcdo`.`Accompagnement` (`nom_article`) VALUES ('nuggets x6');
INSERT INTO `mcdo`.`Accompagnement` (`nom_article`) VALUES ('petites frites');
INSERT INTO `mcdo`.`Accompagnement` (`nom_article`) VALUES ('moyennes frites');
INSERT INTO `mcdo`.`Accompagnement` (`nom_article`) VALUES ('grandes frites');
INSERT INTO `mcdo`.`Accompagnement` (`nom_article`) VALUES ('petites potatoes');
INSERT INTO `mcdo`.`Accompagnement` (`nom_article`) VALUES ('moyennes potatoes');
INSERT INTO `mcdo`.`Accompagnement` (`nom_article`) VALUES ('grandes potatoes');
COMMIT;

-- BOISSONS
START TRANSACTION;
USE `mcdo`;
INSERT INTO `mcdo`.`Boisson` (`nom_article`) VALUES ('petit coca-cola');
INSERT INTO `mcdo`.`Boisson` (`nom_article`) VALUES ('moyen coca-cola');
INSERT INTO `mcdo`.`Boisson` (`nom_article`) VALUES ('grand coca-cola');
INSERT INTO `mcdo`.`Boisson` (`nom_article`) VALUES ('petit ice tea');
INSERT INTO `mcdo`.`Boisson` (`nom_article`) VALUES ('moyen ice tea');
INSERT INTO `mcdo`.`Boisson` (`nom_article`) VALUES ('grand ice tea');
INSERT INTO `mcdo`.`Boisson` (`nom_article`) VALUES ('petit fanta');
INSERT INTO `mcdo`.`Boisson` (`nom_article`) VALUES ('moyen fanta');
INSERT INTO `mcdo`.`Boisson` (`nom_article`) VALUES ('grand fanta');
INSERT INTO `mcdo`.`Boisson` (`nom_article`) VALUES ('evian 50cl');
INSERT INTO `mcdo`.`Boisson` (`nom_article`) VALUES ('badoit 50cl');
INSERT INTO `mcdo`.`Boisson` (`nom_article`) VALUES ('cafe');
INSERT INTO `mcdo`.`Boisson` (`nom_article`) VALUES ('cafe allonge');
INSERT INTO `mcdo`.`Boisson` (`nom_article`) VALUES ('the');
INSERT INTO `mcdo`.`Boisson` (`nom_article`) VALUES ('chocola chaud');
COMMIT;

-- MENU
START TRANSACTION;
USE `mcdo`;
INSERT INTO `mcdo`.`Menu` (`id_menu`, `nom`, `plat`, `boisson`, `accompagnement`) VALUES (0, 'menu big mac', 'big mac', 'grand coca-cola', 'grandes frites');
INSERT INTO `mcdo`.`Menu` (`id_menu`, `nom`, `plat`, `boisson`, `accompagnement`) VALUES (1, 'menu mc chicken', 'mc chicken', 'petit fanta', 'petites frites');
INSERT INTO `mcdo`.`Menu` (`id_menu`, `nom`, `plat`, `boisson`, `accompagnement`) VALUES (2, 'menu salade caesar', 'salade caesar', 'evian 50cl', 'hamburger');
INSERT INTO `mcdo`.`Menu` (`id_menu`, `nom`, `plat`, `boisson`, `accompagnement`) VALUES (3, 'menu nuggets', 'nuggets x20', 'moyen coca-cola', 'moyennes frites');
INSERT INTO `mcdo`.`Menu` (`id_menu`, `nom`, `plat`, `boisson`, `accompagnement`) VALUES (4, 'menu wrap', 'mc wrap poulet bacon', 'grand ice tea', 'cheeseburger');
INSERT INTO `mcdo`.`Menu` (`id_menu`, `nom`, `plat`, `boisson`, `accompagnement`) VALUES (5, 'menu cbo', 'cbo', 'petit fanta', 'petites potatoes');
INSERT INTO `mcdo`.`Menu` (`id_menu`, `nom`, `plat`, `boisson`, `accompagnement`) VALUES (6, 'menu happy meal', 'big mac', 'petit coca-cola', 'petites frites');
INSERT INTO `mcdo`.`Menu` (`id_menu`, `nom`, `plat`, `boisson`, `accompagnement`) VALUES (7, 'menu mc chicken', 'mc chicken', 'grand coca-cola', 'grandes frites');
INSERT INTO `mcdo`.`Menu` (`id_menu`, `nom`, `plat`, `boisson`, `accompagnement`) VALUES (8, 'menu royal deluxe', 'royal deluxe', 'grand ice tea', 'grandes frites');
INSERT INTO `mcdo`.`Menu` (`id_menu`, `nom`, `plat`, `boisson`, `accompagnement`) VALUES (9, 'menu triple cheese', 'triple cheese', 'the', 'nuggets x4');
INSERT INTO `mcdo`.`Menu` (`id_menu`, `nom`, `plat`, `boisson`, `accompagnement`) VALUES (10, 'menu filet-o-fish', 'filet-o-fish', 'evian 50cl', 'moyennes potatoes');
COMMIT;

-- COMMANDE
START TRANSACTION;
USE `mcdo`;
INSERT INTO `mcdo`.`Commande` (`no_commande`, `nom`, `prenom`) VALUES (1,  'dagier', 'thomas');
INSERT INTO `mcdo`.`Commande` (`no_commande`, `nom`, `prenom`) VALUES (2,  'bernasconi', 'dorian');
INSERT INTO `mcdo`.`Commande` (`no_commande`, `nom`, `prenom`) VALUES (3,  'rod', 'quentin');
INSERT INTO `mcdo`.`Commande` (`no_commande`, `nom`, `prenom`) VALUES (4,  'cavat', 'joel');
INSERT INTO `mcdo`.`Commande` (`no_commande`, `nom`, `prenom`) VALUES (5,  'malaspinas', 'orestis');
INSERT INTO `mcdo`.`Commande` (`no_commande`, `nom`, `prenom`) VALUES (6,  'dagier', 'thomas');
INSERT INTO `mcdo`.`Commande` (`no_commande`, `nom`, `prenom`) VALUES (7,  'albuquerque', 'paul');
INSERT INTO `mcdo`.`Commande` (`no_commande`, `nom`, `prenom`) VALUES (8,  'blancy', 'antoine');
INSERT INTO `mcdo`.`Commande` (`no_commande`, `nom`, `prenom`) VALUES (9,  'perret', 'xavier');
INSERT INTO `mcdo`.`Commande` (`no_commande`, `nom`, `prenom`) VALUES (10, 'pesquet', 'thomas');
INSERT INTO `mcdo`.`Commande` (`no_commande`, `nom`, `prenom`) VALUES (11, 'pertuzati', 'gustavo');
INSERT INTO `mcdo`.`Commande` (`no_commande`, `nom`, `prenom`) VALUES (12, 'cavat', 'joel');
INSERT INTO `mcdo`.`Commande` (`no_commande`, `nom`, `prenom`) VALUES (13, 'nguyen', 'trung');
INSERT INTO `mcdo`.`Commande` (`no_commande`, `nom`, `prenom`) VALUES (14, 'dagier', 'thomas');
INSERT INTO `mcdo`.`Commande` (`no_commande`, `nom`, `prenom`) VALUES (15, 'rod', 'quentin');
INSERT INTO `mcdo`.`Commande` (`no_commande`, `nom`, `prenom`) VALUES (16, 'paulot', 'alexey');
INSERT INTO `mcdo`.`Commande` (`no_commande`, `nom`, `prenom`) VALUES (17, 'rod', 'quentin');
INSERT INTO `mcdo`.`Commande` (`no_commande`, `nom`, `prenom`) VALUES (18, 'dagier', 'thomas');
INSERT INTO `mcdo`.`Commande` (`no_commande`, `nom`, `prenom`) VALUES (19, 'lescourt', 'adrien');
INSERT INTO `mcdo`.`Commande` (`no_commande`, `nom`, `prenom`) VALUES (20, 'bernasconi', 'dorian');
COMMIT;

-- COMMANDE-MENU
START TRANSACTION;
USE `mcdo`;
INSERT INTO `mcdo`.`CommandeMenu` (`id_menu`, `no_commande`, `quantite`) VALUES (1, 3, 1);
INSERT INTO `mcdo`.`CommandeMenu` (`id_menu`, `no_commande`, `quantite`) VALUES (2, 4, 2);
INSERT INTO `mcdo`.`CommandeMenu` (`id_menu`, `no_commande`, `quantite`) VALUES (3, 8, 1);
INSERT INTO `mcdo`.`CommandeMenu` (`id_menu`, `no_commande`, `quantite`) VALUES (4, 10, 1);
INSERT INTO `mcdo`.`CommandeMenu` (`id_menu`, `no_commande`, `quantite`) VALUES (5, 12, 3);
INSERT INTO `mcdo`.`CommandeMenu` (`id_menu`, `no_commande`, `quantite`) VALUES (6, 13, 1);
INSERT INTO `mcdo`.`CommandeMenu` (`id_menu`, `no_commande`, `quantite`) VALUES (7, 14, 1);
INSERT INTO `mcdo`.`CommandeMenu` (`id_menu`, `no_commande`, `quantite`) VALUES (8, 16, 2);
INSERT INTO `mcdo`.`CommandeMenu` (`id_menu`, `no_commande`, `quantite`) VALUES (9, 17, 1);
INSERT INTO `mcdo`.`CommandeMenu` (`id_menu`, `no_commande`, `quantite`) VALUES (10, 19, 1);
COMMIT;

-- COMMANDE-ARTICLE
START TRANSACTION;
USE `mcdo`;
INSERT INTO `mcdo`.`CommandeArticle` (`nom_article`, `no_commande`, `quantite`) VALUES ('hamburger', 1, 1);
INSERT INTO `mcdo`.`CommandeArticle` (`nom_article`, `no_commande`, `quantite`) VALUES ('the', 4, 2);
INSERT INTO `mcdo`.`CommandeArticle` (`nom_article`, `no_commande`, `quantite`) VALUES ('grand coca-cola', 6, 1);
INSERT INTO `mcdo`.`CommandeArticle` (`nom_article`, `no_commande`, `quantite`) VALUES ('moyennes frites', 7, 4);
INSERT INTO `mcdo`.`CommandeArticle` (`nom_article`, `no_commande`, `quantite`) VALUES ('cafe allonge', 5, 2);
INSERT INTO `mcdo`.`CommandeArticle` (`nom_article`, `no_commande`, `quantite`) VALUES ('big mac', 15, 1);
INSERT INTO `mcdo`.`CommandeArticle` (`nom_article`, `no_commande`, `quantite`) VALUES ('triple cheese', 2, 3);
INSERT INTO `mcdo`.`CommandeArticle` (`nom_article`, `no_commande`, `quantite`) VALUES ('nuggets x9', 13, 1);
INSERT INTO `mcdo`.`CommandeArticle` (`nom_article`, `no_commande`, `quantite`) VALUES ('moyen ice tea', 9, 1);
INSERT INTO `mcdo`.`CommandeArticle` (`nom_article`, `no_commande`, `quantite`) VALUES ('grandes potatoes', 11, 2);
INSERT INTO `mcdo`.`CommandeArticle` (`nom_article`, `no_commande`, `quantite`) VALUES ('royal deluxe', 20, 1);
COMMIT;