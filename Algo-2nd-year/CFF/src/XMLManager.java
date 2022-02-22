import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerException;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

// on utilise la manière DOM plutôt que SAX c'est plus simple
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

import java.util.Map;

public class XMLManager{
    // lecture du fichier xml donné en paramètre
    // retourne une liste de ville
    public Cities XMLReader(String path){
        File xmlFile = new File(path);
        DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
        List<City> list = new ArrayList<>();
        try {
            DocumentBuilder dBuilder = dbFactory.newDocumentBuilder();
            Document doc = dBuilder.parse(xmlFile);
            doc.getDocumentElement().normalize();
            NodeList cities = doc.getElementsByTagName("ville");            
            NodeList links = doc.getElementsByTagName("liaison");
            for(int i = 0; i < cities.getLength(); i++){
                list.add(getCity(cities.item(i)));
            }
            for(int i = 0; i < links.getLength(); i++){
                updateListCity(list, links.item(i));         
            }
        } catch (Exception e){
            e.printStackTrace();
        }
        return new Cities(list);
    }

    // convertion d'une node du fichier xml en une ville
    private City getCity(Node node){
        if (node.getNodeType() == Node.ELEMENT_NODE){
            Element element = (Element) node;
            String name = element.getElementsByTagName("nom").item(0).getTextContent().trim();
            int latitude = Integer.parseInt(element.getElementsByTagName("latitude").item(0).getTextContent().trim());
            int longitude = Integer.parseInt(element.getElementsByTagName("longitude").item(0).getTextContent().trim());
            return new City(name, latitude, longitude);
        } else {
            throw new RuntimeException("node is not readable");
        }
    }

    // update des voisins pour chaque ville dans la liste
    public void updateListCity(List<City> list, Node node){
        Element element = (Element) node;
        String src = element.getElementsByTagName("vil_1").item(0).getTextContent().trim();
        String dst = element.getElementsByTagName("vil_2").item(0).getTextContent().trim();
        int time = Integer.parseInt(element.getElementsByTagName("temps").item(0).getTextContent().trim());
        for (City city : list) {
            if(city.getName().equals(src)){
                city.addNeighbours(dst, time);
            } else if(city.getName().equals(dst)){
                city.addNeighbours(src, time);
            }
        }
    }

    // création d'une node à partir d'une ville
    public Node getCityXML(Document dom, City c){
        Element ville = dom.createElement("ville");
        Element nom = dom.createElement("nom");
        nom.appendChild(dom.createTextNode(" " + c.getName() + " "));
        ville.appendChild(nom);
        Element longitude = dom.createElement("longitude");
        longitude.appendChild(dom.createTextNode(" " + c.getLongitude().toString() + " "));
        ville.appendChild(longitude);
        Element latitude = dom.createElement("latitude");
        latitude.appendChild(dom.createTextNode(" " + c.getLatitude().toString() + " "));
        ville.appendChild(latitude);
        return ville;
    }

    // création d'une node à partir d'une liaison
    public Node getLinksXML(Document dom, String vil_1, String vil_2, int temps){
        Element liaison = dom.createElement("liaison");
        Element e = dom.createElement("vil_1");
        e.appendChild(dom.createTextNode(" " + vil_1 + " "));
        liaison.appendChild(e);
        e = dom.createElement("vil_2");
        e.appendChild(dom.createTextNode(" " + vil_2 + " "));
        liaison.appendChild(e);
        e = dom.createElement("temps");
        e.appendChild(dom.createTextNode(" " + temps + " "));
        liaison.appendChild(e);
        return liaison;
    }

    // écriture d'un fichier xml à partir d'une liste de villes et de leurs laisons
    public void XMLWriter(Cities cities, String fileName){
        List<City> list = cities.getCities();
        List<City> copy = new ArrayList<>(list);
        try {
            DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
            DocumentBuilder db = dbf.newDocumentBuilder();
            Document dom = db.newDocument();
            Element e = null;
            Element rootEle = dom.createElement("reseau");
            e = dom.createElement("titre");
            e.appendChild(dom.createTextNode(" CFF "));
            rootEle.appendChild(e);
            for(City c : copy){
                rootEle.appendChild(getCityXML(dom, c));
            }
            for(City c : copy){
                Map<String, Integer> neighbours = c.getNeighbours();
                for(String s : neighbours.keySet()){
                    rootEle.appendChild(getLinksXML(dom, c.getName(), s, neighbours.get(s)));
                    for (City city : list){
                        if(city.getName().equals(s)){
                            city.removeNeighbours(c.getName());
                        }
                    }            
                }
            }
            dom.appendChild(rootEle);
            TransformerFactory transformerFactory = TransformerFactory.newInstance();
            Transformer transformer = transformerFactory.newTransformer();
            DOMSource domSource = new DOMSource(dom);
            StreamResult streamResult = new StreamResult(new File(fileName));
            transformer.transform(domSource, streamResult);
        } catch (Exception e) {
            System.out.println("XML: Error while writing file, " + e);
        }
    }
}