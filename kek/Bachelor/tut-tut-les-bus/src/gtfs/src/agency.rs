use std::fs::File;
use std::io::{prelude::*, BufReader};
use std::fmt;

pub struct Agency {
    pub agency_id: String,
    pub agency_name: String,
    pub agency_url: String,
    pub agency_timezone: String,
    pub agency_lang: String,
    pub agency_phone: String,
}

impl From<&Vec<String>> for Agency {
    fn from(v: &Vec<String>) -> Self {
        Agency { 
            agency_id:v[0].to_owned(), 
            agency_name:v[1].to_owned(),
            agency_url:v[2].to_owned(),
            agency_timezone:v[3].to_owned(), 
            agency_lang:v[4].to_owned(), 
            agency_phone:v[5].to_owned() }
    }
}

impl fmt::Display for Agency {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        write!(f, "\"{}\",\"{}\",\"{}\",\"{}\",\"{}\",\"{}\"", 
            self.agency_id, 
            self.agency_name, 
            self.agency_url, 
            self.agency_timezone, 
            self.agency_lang, 
            self.agency_phone)
    }
}

impl PartialEq for Agency {
    fn eq(&self, other: &Agency) -> bool {
        self.agency_id.eq(&other.agency_id) && 
        self.agency_name.eq(&other.agency_name) &&
        self.agency_url.eq(&other.agency_url) &&
        self.agency_timezone.eq(&other.agency_timezone) &&
        self.agency_lang.eq(&other.agency_lang) &&
        self.agency_phone.eq(&other.agency_phone)
    }
}

impl Agency {
    /// Return an option on a vector of Agencies created from a file and a list of names
    ///
    /// # Exemple
    ///
    /// ```
    ///use gtfs::agency::*;
    /// 
    ///let names = ["Transports Publics Genevois"];
    ///let agencies = Agency::read_agencies(&names, "./tpg_input/agency.txt".to_string()).unwrap();
    /// 
    ///let header = "agency_id,agency_name,agency_url,agency_timezone,agency_lang,agency_phone";
    ///write_content(&agencies_vec, "./tpg_output/agency.txt", header);
    /// ```
    pub fn read_agencies(names: &[&str], path: String) -> Option<Vec<Agency>> {
        let reader = BufReader::new(File::open(path).ok()?);
        let mut agencies = reader.lines()
            .flat_map(|line| {
                let v = line.unwrap()
                    .split(',')
                    .map(|word| word.replace('\"', ""))
                    .collect::<Vec<_>>();
                names.iter()
                    .filter(|name| name.contains(&&(v[1])[..]))
                    .map(|_agency_name| Agency::from(&v))
                    .collect::<Vec<_>>()
            })
            .collect::<Vec<_>>();
        agencies.dedup();
        Some(agencies)
    }
}
