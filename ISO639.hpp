
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright 2019 Pedro Vernetti G.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this
 * software and associated documentation files (the "Software"), to deal in the Software
 * without restriction, including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons
 * to whom the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
 * FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#pragma once
#ifndef _OMN_ISO639_INCLUDED
#define _OMN_ISO639_INCLUDED

#include "globalUtilities.hpp"

namespace omn
{
    enum ISO6391LanguageCode : byte
    {
        aa = 1, // Afar
        ab,     // Abkhazian
        af,     // Afrikaans
        ak,     // Akan
        sq,     // Albanian
        am,     // Amharic
        ar,     // Arabic
        an,     // Aragonese
        hy,     // Armenian
        as,     // Assamese
        av,     // Avaric
        ae,     // Avestan
        ay,     // Aymara
        az,     // Azerbaijani / Azeri
        ba,     // Bashkir
        bm,     // Bambara
        eu,     // Basque
        be,     // Belarusian
        bn,     // Bengali
        bh,     // Bihari languages
        bi,     // Bislama
        bs,     // Bosnian
        br,     // Breton
        bg,     // Bulgarian
        my,     // Burmese
        ca,     // Catalan / Valencian
        ch,     // Chamorro
        ce,     // Chechen
        zh,     // Chinese
        cu,     // Old Church Slavonic
        cv,     // Chuvash
        kw,     // Cornish
        co,     // Corsican
        cr,     // Cree
        cs,     // Czech
        da,     // Danish
        dv,     // Divehi
        nl,     // Dutch
        dz,     // Dzongkha
        en,     // English
        eo,     // Esperanto
        et,     // Estonian
        ee,     // Ewe
        fo,     // Faroese
        fj,     // Fijian
        fi,     // Finnish
        fr,     // French
        fy,     // Western Frisian
        ff,     // Fulah
        ka,     // Georgian
        de,     // German
        gd,     // Scottish Gaelic
        ga,     // Irish
        gl,     // Galician
        gv,     // Manx
        el,     // Greek
        gn,     // Guarani
        gu,     // Gujarati
        ht,     // Haitian Creole
        ha,     // Hausa
        he,     // Hebrew
        hz,     // Herero
        hi,     // Hindi
        ho,     // Hiri Motu
        hr,     // Croatian
        hu,     // Hungarian
        ig,     // Igbo
        is,     // Icelandic
        io,     // Ido
        ii,     // Sichuan Yi / Nuosu
        iu,     // Inuktitut
        ie,     // Interlingue
        ia,     // Interlingua
        id,     // Indonesian
        ik,     // Inupiaq
        it,     // Italian
        jv,     // Javanese
        ja,     // Japanese
        kl,     // Greenlandic
        kn,     // Kannada
        ks,     // Kashmiri
        kr,     // Kanuri
        kk,     // Kazakh
        km,     // Khmer
        ki,     // Kikuyu
        rw,     // Kinyarwanda
        ky,     // Kyrgyz
        kv,     // Komi
        kg,     // Kongo
        ko,     // Korean
        kj,     // Kwanyama
        ku,     // Kurdish
        lo,     // Lao
        la,     // Latin
        lv,     // Latvian
        li,     // Limburgish
        ln,     // Lingala
        lt,     // Lithuanian
        lb,     // Luxembourgish
        lu,     // Luba-Katanga
        lg,     // Ganda
        mk,     // Macedonian
        mh,     // Marshallese
        ml,     // Malayalam
        mi,     // Maori
        mr,     // Marathi
        ms,     // Malay
        mg,     // Malagasy
        mt,     // Maltese
        mn,     // Mongolian
        na,     // Nauru
        nv,     // Navajo
        nr,     // Southern Ndebele
        nd,     // Northern Ndebele
        ng,     // Ndonga
        ne,     // Nepali
        no,     // Norwegian
        ny,     // Chichewa
        oc,     // Occitan
        oj,     // Ojibwa
        or_,    // Oriya
        om,     // Oromo
        os,     // Ossetian
        pa,     // Punjabi
        fa,     // Persian
        pi,     // Pali
        pl,     // Polish
        pt,     // Portuguese
        ps,     // Pashto
        qu,     // Quechua
        rm,     // Romansh
        ro,     // Romanian
        rn,     // Rundi
        ru,     // Russian
        sg,     // Sango
        sa,     // Sanskrit
        si,     // Sinhalese
        sk,     // Slovak
        sl,     // Slovenian
        se,     // Northern Sami
        sm,     // Samoan
        sn,     // Shona
        sd,     // Sindhi
        so,     // Somali
        st,     // Sotho
        es,     // Spanish
        sc,     // Sardinian
        sr,     // Serbian
        ss,     // Swati
        su,     // Sundanese
        sw,     // Swahili
        sv,     // Swedish
        ty,     // Tahitian
        ta,     // Tamil
        tt,     // Tatar
        te,     // Telugu
        tg,     // Tajik
        tl,     // Tagalog
        th,     // Thai
        bo,     // Tibetan
        ti,     // Tigrinya
        to,     // Tonga
        tn,     // Tswana
        ts,     // Tsonga
        tk,     // Turkmen
        tr,     // Turkish
        tw,     // Twi
        ug,     // Uighur
        uk,     // Ukrainian
        ur,     // Urdu
        uz,     // Uzbek
        ve,     // Venda
        vi,     // Vietnamese
        vo,     // Volapuk
        cy,     // Welsh
        wa,     // Walloon
        wo,     // Wolof
        xh,     // Xhosa
        yi,     // Yiddish
        yo,     // Yoruba
        za,     // Zhuang
        zu      // Zulu
    };

    enum ISO6392LanguageCode : uint16_t
    {
        und = ((uint16_t)(-1)),         // undefined
        zxx = 0,                        // no linguistic content
        aar = ISO6391LanguageCode::aa,  // Afar
        abk = ISO6391LanguageCode::ab,  // Abkhazian
        afr = ISO6391LanguageCode::af,  // Afrikaans
        aka = ISO6391LanguageCode::ak,  // Akan
        alb = ISO6391LanguageCode::sq,  // Albanian [B-code]
        amh = ISO6391LanguageCode::am,  // Amharic
        ara = ISO6391LanguageCode::ar,  // Arabic
        arg = ISO6391LanguageCode::an,  // Aragonese
        arm = ISO6391LanguageCode::hy,  // Armenian [B-code]
        asm_ = ISO6391LanguageCode::as, // Assamese
        ava = ISO6391LanguageCode::av,  // Avaric
        ave = ISO6391LanguageCode::ae,  // Avestan
        aym = ISO6391LanguageCode::ay,  // Aymara
        aze = ISO6391LanguageCode::az,  // Azerbaijani / Azeri
        bak = ISO6391LanguageCode::ba,  // Bashkir
        bam = ISO6391LanguageCode::bm,  // Bambara
        baq = ISO6391LanguageCode::eu,  // Basque [B-code]
        bel = ISO6391LanguageCode::be,  // Belarusian
        ben = ISO6391LanguageCode::bn,  // Bengali
        bih = ISO6391LanguageCode::bh,  // Bihari languages
        bis = ISO6391LanguageCode::bi,  // Bislama
        bos = ISO6391LanguageCode::bs,  // Bosnian
        bre = ISO6391LanguageCode::br,  // Breton
        bul = ISO6391LanguageCode::bg,  // Bulgarian
        bur = ISO6391LanguageCode::my,  // Burmese [B-code]
        cat = ISO6391LanguageCode::ca,  // Catalan / Valencian
        cha = ISO6391LanguageCode::ch,  // Chamorro
        che = ISO6391LanguageCode::ce,  // Chechen
        chi = ISO6391LanguageCode::zh,  // Chinese [B-code]
        chu = ISO6391LanguageCode::cu,  // Old Church Slavonic
        chv = ISO6391LanguageCode::cv,  // Chuvash
        cor = ISO6391LanguageCode::kw,  // Cornish
        cos = ISO6391LanguageCode::co,  // Corsican
        cre = ISO6391LanguageCode::cr,  // Cree
        cze = ISO6391LanguageCode::cs,  // Czech [B-code]
        dan = ISO6391LanguageCode::da,  // Danish
        div = ISO6391LanguageCode::dv,  // Divehi
        dut = ISO6391LanguageCode::nl,  // Dutch [B-code]
        dzo = ISO6391LanguageCode::dz,  // Dzongkha
        eng = ISO6391LanguageCode::en,  // English
        epo = ISO6391LanguageCode::eo,  // Esperanto
        est = ISO6391LanguageCode::et,  // Estonian
        ewe = ISO6391LanguageCode::ee,  // Ewe
        fao = ISO6391LanguageCode::fo,  // Faroese
        fij = ISO6391LanguageCode::fj,  // Fijian
        fin = ISO6391LanguageCode::fi,  // Finnish
        fre = ISO6391LanguageCode::fr,  // French [B-code]
        fry = ISO6391LanguageCode::fy,  // Western Frisian
        ful = ISO6391LanguageCode::ff,  // Fulah
        geo = ISO6391LanguageCode::ka,  // Georgian [B-code]
        ger = ISO6391LanguageCode::de,  // German [B-code]
        gla = ISO6391LanguageCode::gd,  // Scottish Gaelic
        gle = ISO6391LanguageCode::ga,  // Irish
        glg = ISO6391LanguageCode::gl,  // Galician
        glv = ISO6391LanguageCode::gv,  // Manx
        gre = ISO6391LanguageCode::el,  // Greek [B-code]
        grn = ISO6391LanguageCode::gn,  // Guarani
        guj = ISO6391LanguageCode::gu,  // Gujarati
        hat = ISO6391LanguageCode::ht,  // Haitian Creole
        hau = ISO6391LanguageCode::ha,  // Hausa
        heb = ISO6391LanguageCode::he,  // Hebrew
        her = ISO6391LanguageCode::hz,  // Herero
        hin = ISO6391LanguageCode::hi,  // Hindi
        hmo = ISO6391LanguageCode::ho,  // Hiri Motu
        hrv = ISO6391LanguageCode::hr,  // Croatian
        hun = ISO6391LanguageCode::hu,  // Hungarian
        ibo = ISO6391LanguageCode::ig,  // Igbo
        ice = ISO6391LanguageCode::is,  // Icelandic [B-code]
        ido = ISO6391LanguageCode::io,  // Ido
        iii = ISO6391LanguageCode::ii,  // Sichuan Yi / Nuosu
        iku = ISO6391LanguageCode::iu,  // Inuktitut
        ile = ISO6391LanguageCode::ie,  // Interlingue
        ina = ISO6391LanguageCode::ia,  // Interlingua
        ind = ISO6391LanguageCode::id,  // Indonesian
        ipk = ISO6391LanguageCode::ik,  // Inupiaq
        ita = ISO6391LanguageCode::it,  // Italian
        jav = ISO6391LanguageCode::jv,  // Javanese
        jpn = ISO6391LanguageCode::ja,  // Japanese
        kal = ISO6391LanguageCode::kl,  // Greenlandic
        kan = ISO6391LanguageCode::kn,  // Kannada
        kas = ISO6391LanguageCode::ks,  // Kashmiri
        kau = ISO6391LanguageCode::kr,  // Kanuri
        kaz = ISO6391LanguageCode::kk,  // Kazakh
        khm = ISO6391LanguageCode::km,  // Khmer
        kik = ISO6391LanguageCode::ki,  // Kikuyu
        kin = ISO6391LanguageCode::rw,  // Kinyarwanda
        kir = ISO6391LanguageCode::ky,  // Kyrgyz
        kom = ISO6391LanguageCode::kv,  // Komi
        kon = ISO6391LanguageCode::kg,  // Kongo
        kor = ISO6391LanguageCode::ko,  // Korean
        kua = ISO6391LanguageCode::kj,  // Kwanyama
        kur = ISO6391LanguageCode::ku,  // Kurdish
        lao = ISO6391LanguageCode::lo,  // Lao
        lat = ISO6391LanguageCode::la,  // Latin
        lav = ISO6391LanguageCode::lv,  // Latvian
        lim = ISO6391LanguageCode::li,  // Limburgish
        lin = ISO6391LanguageCode::ln,  // Lingala
        lit = ISO6391LanguageCode::lt,  // Lithuanian
        ltz = ISO6391LanguageCode::lb,  // Luxembourgish
        lub = ISO6391LanguageCode::lu,  // Luba-Katanga
        lug = ISO6391LanguageCode::lg,  // Ganda
        mac = ISO6391LanguageCode::mk,  // Macedonian [B-code]
        mah = ISO6391LanguageCode::mh,  // Marshallese
        mal = ISO6391LanguageCode::ml,  // Malayalam
        mao = ISO6391LanguageCode::mi,  // Maori [B-code]
        mar = ISO6391LanguageCode::mr,  // Marathi
        may = ISO6391LanguageCode::ms,  // Malay [B-code]
        mlg = ISO6391LanguageCode::mg,  // Malagasy
        mlt = ISO6391LanguageCode::mt,  // Maltese
        mon = ISO6391LanguageCode::mn,  // Mongolian
        nau = ISO6391LanguageCode::na,  // Nauru
        nav = ISO6391LanguageCode::nv,  // Navajo
        nbl = ISO6391LanguageCode::nr,  // Southern Ndebele
        nde = ISO6391LanguageCode::nd,  // Northern Ndebele
        ndo = ISO6391LanguageCode::ng,  // Ndonga
        nep = ISO6391LanguageCode::ne,  // Nepali
        nor = ISO6391LanguageCode::no,  // Norwegian
        nya = ISO6391LanguageCode::ny,  // Chichewa
        oci = ISO6391LanguageCode::oc,  // Occitan
        oji = ISO6391LanguageCode::oj,  // Ojibwa
        ori = ISO6391LanguageCode::or_, // Oriya
        orm = ISO6391LanguageCode::om,  // Oromo
        oss = ISO6391LanguageCode::os,  // Ossetian
        pan = ISO6391LanguageCode::pa,  // Punjabi
        per = ISO6391LanguageCode::fa,  // Persian [B-code]
        pli = ISO6391LanguageCode::pi,  // Pali
        pol = ISO6391LanguageCode::pl,  // Polish
        por = ISO6391LanguageCode::pt,  // Portuguese
        pus = ISO6391LanguageCode::ps,  // Pashto
        que = ISO6391LanguageCode::qu,  // Quechua
        roh = ISO6391LanguageCode::rm,  // Romansh
        rum = ISO6391LanguageCode::ro,  // Romanian [B-code]
        run = ISO6391LanguageCode::rn,  // Rundi
        rus = ISO6391LanguageCode::ru,  // Russian
        sag = ISO6391LanguageCode::sg,  // Sango
        san = ISO6391LanguageCode::sa,  // Sanskrit
        sin = ISO6391LanguageCode::si,  // Sinhalese
        slo = ISO6391LanguageCode::sk,  // Slovak [B-code]
        slv = ISO6391LanguageCode::sl,  // Slovenian
        sme = ISO6391LanguageCode::se,  // Northern Sami
        smo = ISO6391LanguageCode::sm,  // Samoan
        sna = ISO6391LanguageCode::sn,  // Shona
        snd = ISO6391LanguageCode::sd,  // Sindhi
        som = ISO6391LanguageCode::so,  // Somali
        sot = ISO6391LanguageCode::st,  // Sotho
        spa = ISO6391LanguageCode::es,  // Spanish
        srd = ISO6391LanguageCode::sc,  // Sardinian
        srp = ISO6391LanguageCode::sr,  // Serbian
        ssw = ISO6391LanguageCode::ss,  // Swati
        sun = ISO6391LanguageCode::su,  // Sundanese
        swa = ISO6391LanguageCode::sw,  // Swahili
        swe = ISO6391LanguageCode::sv,  // Swedish
        tah = ISO6391LanguageCode::ty,  // Tahitian
        tam = ISO6391LanguageCode::ta,  // Tamil
        tat = ISO6391LanguageCode::tt,  // Tatar
        tel = ISO6391LanguageCode::te,  // Telugu
        tgk = ISO6391LanguageCode::tg,  // Tajik
        tgl = ISO6391LanguageCode::tl,  // Tagalog
        tha = ISO6391LanguageCode::th,  // Thai
        tib = ISO6391LanguageCode::bo,  // Tibetan [B-code]
        tir = ISO6391LanguageCode::ti,  // Tigrinya
        ton = ISO6391LanguageCode::to,  // Tonga
        tsn = ISO6391LanguageCode::tn,  // Tswana
        tso = ISO6391LanguageCode::ts,  // Tsonga
        tuk = ISO6391LanguageCode::tk,  // Turkmen
        tur = ISO6391LanguageCode::tr,  // Turkish
        twi = ISO6391LanguageCode::tw,  // Twi
        uig = ISO6391LanguageCode::ug,  // Uighur
        ukr = ISO6391LanguageCode::uk,  // Ukrainian
        urd = ISO6391LanguageCode::ur,  // Urdu
        uzb = ISO6391LanguageCode::uz,  // Uzbek
        ven = ISO6391LanguageCode::ve,  // Venda
        vie = ISO6391LanguageCode::vi,  // Vietnamese
        vol = ISO6391LanguageCode::vo,  // Volapuk
        wel = ISO6391LanguageCode::cy,  // Welsh [B-code]
        wln = ISO6391LanguageCode::wa,  // Walloon
        wol = ISO6391LanguageCode::wo,  // Wolof
        xho = ISO6391LanguageCode::xh,  // Xhosa
        yid = ISO6391LanguageCode::yi,  // Yiddish
        yor = ISO6391LanguageCode::yo,  // Yoruba
        zha = ISO6391LanguageCode::za,  // Zhuang
        zul = ISO6391LanguageCode::zu,  // Zulu
        ace,  // Achinese
        ach,  // Acoli
        ada,  // Adangme
        ady,  // Adyghe
        afh,  // Afrihili
        ain,  // Ainu
        akk,  // Akkadian
        ale,  // Aleut
        alg,  // Algonquian languages
        alt,  // Southern Altai
        ang,  // Old English
        anp,  // Angika
        apa,  // Apache languages
        arc,  // Official Aramaic / Imperial Aramaic
        arn,  // Mapudungun
        arp,  // Arapaho
        arw,  // Arawak
        ast,  // Asturian / Leonese
        ath,  // Athapascan languages
        aus,  // Australian languages
        awa,  // Awadhi
        bad,  // Banda languages
        bai,  // Bamileke languages
        bal,  // Baluchi
        ban,  // Balinese
        bas,  // Basa
        bej,  // Beja
        bem,  // Bemba
        ber,  // Berber languages
        bho,  // Bhojpuri
        bik,  // Bikol
        bin,  // Bini / Edo
        bla,  // Siksika
        bra,  // Braj
        btk,  // Batak languages
        bua,  // Buriat
        bug,  // Buginese
        byn,  // Bilin
        cad,  // Caddo
        cai,  // Mesoamerican languages
        car,  // Carib
        ceb,  // Cebuano
        chb,  // Chibcha
        chg,  // Chagatai
        chk,  // Chuukese
        chm,  // Mari
        chn,  // Chinook jargon
        cho,  // Choctaw
        chp,  // Chipewyan
        chr,  // Cherokee
        chy,  // Cheyenne
        cmc,  // Chamic languages
        cnr,  // Montenegrin
        cop,  // Coptic
        cpe,  // English creoles
        cpf,  // French creoles
        cpp,  // Portuguese creoles
        crh,  // Crimean Tatar
        csb,  // Kashubian
        dak,  // Dakota
        dar,  // Dargwa
        day,  // Land Dayak languages
        del,  // Delaware
        den,  // Slavey
        dgr,  // Dogrib
        din,  // Dinka
        doi,  // Dogri
        dsb,  // Lower Sorbian
        dua,  // Duala
        dum,  // Middle Dutch
        dyu,  // Dyula
        efi,  // Efik
        egy,  // Egyptian
        eka,  // Ekajuk
        elx,  // Elamite
        enm,  // Middle English
        ewo,  // Ewondo
        fan,  // Fang
        fat,  // Fanti
        fon,  // Fon
        frm,  // Middle French
        fro,  // Old French
        frr,  // Northern Frisian
        frs,  // Eastern Frisian
        fur,  // Friulian
        gaa,  // Ga
        gay,  // Gayo
        gba,  // Gbaya
        gez,  // Geez
        gil,  // Gilbertese
        gmh,  // Middle High German
        goh,  // Old High German
        gon,  // Gondi
        gor,  // Gorontalo
        got,  // Gothic
        grb,  // Grebo
        grc,  // Ancient Greek
        gsw,  // Swiss German / Alemannic
        gwi,  // Gwich'in
        hai,  // Haida
        haw,  // Hawaiian
        hil,  // Hiligaynon
        him,  // Himachali languages
        hit,  // Hittite
        hmn,  // Hmong
        hsb,  // Upper Sorbian
        hup,  // Hupa
        iba,  // Iban
        ijo,  // Ijo languages
        ilo,  // Iloko
        inh,  // Ingush
        iro,  // Iroquoian languages
        jbo,  // Lojban
        jpr,  // Judeo-Persian
        jrb,  // Judeo-Arabic
        kaa,  // Kara-Kalpak
        kab,  // Kabyle
        kac,  // Kachin / Jingpho
        kam,  // Kamba
        kar,  // Karen languages
        kaw,  // Kawi
        kbd,  // Kabardian
        kha,  // Khasi
        khi,  // Khoisan languages
        kho,  // Khotanese / Sakan
        kmb,  // Kimbundu
        kok,  // Konkani
        kos,  // Kosraean
        kpe,  // Kpelle
        krc,  // Karachay-Balkar
        krl,  // Karelian
        kro,  // Kru languages
        kru,  // Kurukh
        kum,  // Kumyk
        kut,  // Kutenai
        lad,  // Ladino
        lah,  // Lahnda
        lam,  // Lamba
        lez,  // Lezghian
        lol,  // Mongo
        loz,  // Lozi
        lua,  // Luba-Lulua
        lui,  // Luiseno
        lun,  // Lunda
        luo,  // Luo
        lus,  // Lushai
        mad,  // Madurese
        mag,  // Magahi
        mai,  // Maithili
        mak,  // Makasar
        man,  // Mandingo
        mas,  // Masai
        mdf,  // Moksha
        mdr,  // Mandar
        men,  // Mende
        mga,  // Middle Irish
        mic,  // Micmac
        min,  // Minangkabau
        mis,  // uncoded languages
        mkh,  // Mon-Khmer languages
        mnc,  // Manchu
        mni,  // Manipuri
        mno,  // Manobo languages
        moh,  // Mohawk
        mos,  // Mossi
        mul,  // multiple languages
        mun,  // Munda languages
        mus,  // Creek
        mwl,  // Mirandese
        mwr,  // Marwari
        myn,  // Mayan languages
        myv,  // Erzya
        nah,  // Nahuatl languages
        nai,  // Indigenous North American languages
        nap,  // Neapolitan
        nds,  // Low German / Low Saxon
        new_, // Newari
        nia,  // Nias
        niu,  // Niuean
        nog,  // Nogai
        non,  // Old Norse
        nqo,  // N'Ko
        nso,  // Sepedi / Northern Sotho
        nub,  // Nubian languages
        nwc,  // Old Newari / Classical Newari
        nym,  // Nyamwezi
        nyn,  // Nyankole
        nyo,  // Nyoro
        nzi,  // Nzima
        osa,  // Osage
        ota,  // Ottoman Turkish
        oto,  // Otomian languages
        paa,  // Papuan languages
        pag,  // Pangasinan
        pal,  // Pahlavi
        pam,  // Pampanga
        pap,  // Papiamento
        pau,  // Palauan
        peo,  // Old Persian
        phi,  // Philippine languages
        phn,  // Phoenician
        pon,  // Pohnpeian
        pra,  // Prakrit languages
        pro,  // Old Occitan / Old Provencal
        raj,  // Rajasthani
        rap,  // Rapanui
        rar,  // Rarotongan / Cook Islands Maori
        rom,  // Romany
        rup,  // Aromanian
        sad,  // Sandawe
        sah,  // Yakut
        sai,  // Indigenous South American language
        sal,  // Salishan languages
        sam,  // Samaritan
        sas,  // Sasak
        sat,  // Santali
        scn,  // Sicilian
        sco,  // Scots
        sel,  // Selkup
        sga,  // Old Irish
        shn,  // Shan
        sid,  // Sidamo
        sio,  // Siouan languages
        sma,  // Southern Sami
        smj,  // Lule Sami
        smn,  // Inari Sami
        sms,  // Skolt Sami
        snk,  // Soninke
        sog,  // Sogdian
        son,  // Songhai languages
        srn,  // Sranan Tongo
        srr,  // Serer
        suk,  // Sukuma
        sus,  // Susu
        sux,  // Sumerian
        syc,  // Classical Syriac
        syr,  // Syriac
        tai,  // Tai languages
        tem,  // Timne
        ter,  // Tereno
        tet,  // Tetum
        tig,  // Tigre
        tiv,  // Tiv
        tkl,  // Tokelau
        tlh,  // Klingon
        tli,  // Tlingit
        tmh,  // Tamashek
        tog,  // Tonga (Nyasa)
        tpi,  // Tok Pisin
        tsi,  // Tsimshian
        tum,  // Tumbuka
        tup,  // Tupi languages
        tut,  // Altaic languages
        tvl,  // Tuvalu
        tyv,  // Tuvinian
        udm,  // Udmurt
        uga,  // Ugaritic
        umb,  // Umbundu
        vai,  // Vai
        vot,  // Votic
        wak,  // Wakashan languages
        wal,  // Walamo
        war,  // Waray
        was,  // Washo
        wen,  // Sorbian languages
        xal,  // Kalmyk / Oirat
        yao,  // Yao
        yap,  // Yapese
        ypk,  // Yupik languages
        zap,  // Zapotec
        zbl,  // Blissymbols
        zen,  // Zenaga
        zgh,  // Tamazight
        znd,  // Zande languages
        zun,  // Zuni
        zza,  // Zaza / Dimili / Kirdki / Zazaki

        // Alternative terminological codes (T-codes)
        bod = tib, // Tibetan
        ces = cze, // Czech
        cym = wel, // Welsh
        deu = ger, // German
        ell = gre, // Greek
        eus = baq, // Basque
        fas = per, // Persian
        fra = fre, // French
        hye = arm, // Armenian
        isl = ice, // Icelandic
        kat = geo, // Georgian
        mkd = mac, // Macedonian
        mri = mao, // Maori
        msa = may, // Malay
        mya = bur, // Burmese
        nld = dut, // Dutch
        ron = rum, // Romanian
        slk = slo, // Slovak
        sqi = alb, // Albanian
        zho = chi, // Chinese

        // Languages treated here as being the same
        fil = tgl  // Filipino / Tagalog
    };

    using language = ISO6392LanguageCode;
}

namespace // internal parts
{
    constexpr const uint16_t ISO6391CodesCount = omn::ISO6391LanguageCode::zu + 1;

    constexpr const omn::unicode::UTF8Character * ISO6391CodeStrings[ISO6391CodesCount] =
    {
        u8"aa",
        u8"ab",
        u8"af",
        u8"ak",
        u8"sq",
        u8"am",
        u8"ar",
        u8"an",
        u8"hy",
        u8"as",
        u8"av",
        u8"ae",
        u8"ay",
        u8"az",
        u8"ba",
        u8"bm",
        u8"eu",
        u8"be",
        u8"bn",
        u8"bh",
        u8"bi",
        u8"bs",
        u8"br",
        u8"bg",
        u8"my",
        u8"ca",
        u8"ch",
        u8"ce",
        u8"zh",
        u8"cu",
        u8"cv",
        u8"kw",
        u8"co",
        u8"cr",
        u8"cs",
        u8"da",
        u8"dv",
        u8"nl",
        u8"dz",
        u8"en",
        u8"eo",
        u8"et",
        u8"ee",
        u8"fo",
        u8"fj",
        u8"fi",
        u8"fr",
        u8"fy",
        u8"ff",
        u8"ka",
        u8"de",
        u8"gd",
        u8"ga",
        u8"gl",
        u8"gv",
        u8"el",
        u8"gn",
        u8"gu",
        u8"ht",
        u8"ha",
        u8"he",
        u8"hz",
        u8"hi",
        u8"ho",
        u8"hr",
        u8"hu",
        u8"ig",
        u8"is",
        u8"io",
        u8"ii",
        u8"iu",
        u8"ie",
        u8"ia",
        u8"id",
        u8"ik",
        u8"it",
        u8"jv",
        u8"ja",
        u8"kl",
        u8"kn",
        u8"ks",
        u8"kr",
        u8"kk",
        u8"km",
        u8"ki",
        u8"rw",
        u8"ky",
        u8"kv",
        u8"kg",
        u8"ko",
        u8"kj",
        u8"ku",
        u8"lo",
        u8"la",
        u8"lv",
        u8"li",
        u8"ln",
        u8"lt",
        u8"lb",
        u8"lu",
        u8"lg",
        u8"mk",
        u8"mh",
        u8"ml",
        u8"mi",
        u8"mr",
        u8"ms",
        u8"mg",
        u8"mt",
        u8"mn",
        u8"na",
        u8"nv",
        u8"nr",
        u8"nd",
        u8"ng",
        u8"ne",
        u8"no",
        u8"ny",
        u8"oc",
        u8"oj",
        u8"or",
        u8"om",
        u8"os",
        u8"pa",
        u8"fa",
        u8"pi",
        u8"pl",
        u8"pt",
        u8"ps",
        u8"qu",
        u8"rm",
        u8"ro",
        u8"rn",
        u8"ru",
        u8"sg",
        u8"sa",
        u8"si",
        u8"sk",
        u8"sl",
        u8"se",
        u8"sm",
        u8"sn",
        u8"sd",
        u8"so",
        u8"st",
        u8"es",
        u8"sc",
        u8"sr",
        u8"ss",
        u8"su",
        u8"sw",
        u8"sv",
        u8"ty",
        u8"ta",
        u8"tt",
        u8"te",
        u8"tg",
        u8"tl",
        u8"th",
        u8"bo",
        u8"ti",
        u8"to",
        u8"tn",
        u8"ts",
        u8"tk",
        u8"tr",
        u8"tw",
        u8"ug",
        u8"uk",
        u8"ur",
        u8"uz",
        u8"ve",
        u8"vi",
        u8"vo",
        u8"cy",
        u8"wa",
        u8"wo",
        u8"xh",
        u8"yi",
        u8"yo",
        u8"za",
        u8"zu"
    };

    constexpr const uint16_t ISO6392CodesCount = omn::ISO6392LanguageCode::zza + 2;

    constexpr const omn::unicode::UTF8Character * ISO6392CodeStrings[ISO6392CodesCount] =
    {
        u8"zxx",
        u8"aar",
        u8"abk",
        u8"afr",
        u8"aka",
        u8"alb",
        u8"amh",
        u8"ara",
        u8"arg",
        u8"arm",
        u8"asm",
        u8"ava",
        u8"ave",
        u8"aym",
        u8"aze",
        u8"bak",
        u8"bam",
        u8"baq",
        u8"bel",
        u8"ben",
        u8"bih",
        u8"bis",
        u8"bos",
        u8"bre",
        u8"bul",
        u8"bur",
        u8"cat",
        u8"cha",
        u8"che",
        u8"chi",
        u8"chu",
        u8"chv",
        u8"cor",
        u8"cos",
        u8"cre",
        u8"cze",
        u8"dan",
        u8"div",
        u8"dut",
        u8"dzo",
        u8"eng",
        u8"epo",
        u8"est",
        u8"ewe",
        u8"fao",
        u8"fij",
        u8"fin",
        u8"fre",
        u8"fry",
        u8"ful",
        u8"geo",
        u8"ger",
        u8"gla",
        u8"gle",
        u8"glg",
        u8"glv",
        u8"gre",
        u8"grn",
        u8"guj",
        u8"hat",
        u8"hau",
        u8"heb",
        u8"her",
        u8"hin",
        u8"hmo",
        u8"hrv",
        u8"hun",
        u8"ibo",
        u8"ice",
        u8"ido",
        u8"iii",
        u8"iku",
        u8"ile",
        u8"ina",
        u8"ind",
        u8"ipk",
        u8"ita",
        u8"jav",
        u8"jpn",
        u8"kal",
        u8"kan",
        u8"kas",
        u8"kau",
        u8"kaz",
        u8"khm",
        u8"kik",
        u8"kin",
        u8"kir",
        u8"kom",
        u8"kon",
        u8"kor",
        u8"kua",
        u8"kur",
        u8"lao",
        u8"lat",
        u8"lav",
        u8"lim",
        u8"lin",
        u8"lit",
        u8"ltz",
        u8"lub",
        u8"lug",
        u8"mac",
        u8"mah",
        u8"mal",
        u8"mao",
        u8"mar",
        u8"may",
        u8"mlg",
        u8"mlt",
        u8"mon",
        u8"nau",
        u8"nav",
        u8"nbl",
        u8"nde",
        u8"ndo",
        u8"nep",
        u8"nor",
        u8"nya",
        u8"oci",
        u8"oji",
        u8"ori",
        u8"orm",
        u8"oss",
        u8"pan",
        u8"per",
        u8"pli",
        u8"pol",
        u8"por",
        u8"pus",
        u8"que",
        u8"roh",
        u8"rum",
        u8"run",
        u8"rus",
        u8"sag",
        u8"san",
        u8"sin",
        u8"slo",
        u8"slv",
        u8"sme",
        u8"smo",
        u8"sna",
        u8"snd",
        u8"som",
        u8"sot",
        u8"spa",
        u8"srd",
        u8"srp",
        u8"ssw",
        u8"sun",
        u8"swa",
        u8"swe",
        u8"tah",
        u8"tam",
        u8"tat",
        u8"tel",
        u8"tgk",
        u8"tgl",
        u8"tha",
        u8"tib",
        u8"tir",
        u8"ton",
        u8"tsn",
        u8"tso",
        u8"tuk",
        u8"tur",
        u8"twi",
        u8"uig",
        u8"ukr",
        u8"urd",
        u8"uzb",
        u8"ven",
        u8"vie",
        u8"vol",
        u8"wel",
        u8"wln",
        u8"wol",
        u8"xho",
        u8"yid",
        u8"yor",
        u8"zha",
        u8"zul",
        u8"ace",
        u8"ach",
        u8"ada",
        u8"ady",
        u8"afh",
        u8"ain",
        u8"akk",
        u8"ale",
        u8"alg",
        u8"alt",
        u8"ang",
        u8"anp",
        u8"apa",
        u8"arc",
        u8"arn",
        u8"arp",
        u8"arw",
        u8"ast",
        u8"ath",
        u8"aus",
        u8"awa",
        u8"bad",
        u8"bai",
        u8"bal",
        u8"ban",
        u8"bas",
        u8"bej",
        u8"bem",
        u8"ber",
        u8"bho",
        u8"bik",
        u8"bin",
        u8"bla",
        u8"bra",
        u8"btk",
        u8"bua",
        u8"bug",
        u8"byn",
        u8"cad",
        u8"cai",
        u8"car",
        u8"ceb",
        u8"chb",
        u8"chg",
        u8"chk",
        u8"chm",
        u8"chn",
        u8"cho",
        u8"chp",
        u8"chr",
        u8"chy",
        u8"cmc",
        u8"cnr",
        u8"cop",
        u8"cpe",
        u8"cpf",
        u8"cpp",
        u8"crh",
        u8"csb",
        u8"dak",
        u8"dar",
        u8"day",
        u8"del",
        u8"den",
        u8"dgr",
        u8"din",
        u8"doi",
        u8"dsb",
        u8"dua",
        u8"dum",
        u8"dyu",
        u8"efi",
        u8"egy",
        u8"eka",
        u8"elx",
        u8"enm",
        u8"ewo",
        u8"fan",
        u8"fat",
        u8"fon",
        u8"frm",
        u8"fro",
        u8"frr",
        u8"frs",
        u8"fur",
        u8"gaa",
        u8"gay",
        u8"gba",
        u8"gez",
        u8"gil",
        u8"gmh",
        u8"goh",
        u8"gon",
        u8"gor",
        u8"got",
        u8"grb",
        u8"grc",
        u8"gsw",
        u8"gwi",
        u8"hai",
        u8"haw",
        u8"hil",
        u8"him",
        u8"hit",
        u8"hmn",
        u8"hsb",
        u8"hup",
        u8"iba",
        u8"ijo",
        u8"ilo",
        u8"inh",
        u8"iro",
        u8"jbo",
        u8"jpr",
        u8"jrb",
        u8"kaa",
        u8"kab",
        u8"kac",
        u8"kam",
        u8"kar",
        u8"kaw",
        u8"kbd",
        u8"kha",
        u8"khi",
        u8"kho",
        u8"kmb",
        u8"kok",
        u8"kos",
        u8"kpe",
        u8"krc",
        u8"krl",
        u8"kro",
        u8"kru",
        u8"kum",
        u8"kut",
        u8"lad",
        u8"lah",
        u8"lam",
        u8"lez",
        u8"lol",
        u8"loz",
        u8"lua",
        u8"lui",
        u8"lun",
        u8"luo",
        u8"lus",
        u8"mad",
        u8"mag",
        u8"mai",
        u8"mak",
        u8"man",
        u8"mas",
        u8"mdf",
        u8"mdr",
        u8"men",
        u8"mga",
        u8"mic",
        u8"min",
        u8"mis",
        u8"mkh",
        u8"mnc",
        u8"mni",
        u8"mno",
        u8"moh",
        u8"mos",
        u8"mul",
        u8"mun",
        u8"mus",
        u8"mwl",
        u8"mwr",
        u8"myn",
        u8"myv",
        u8"nah",
        u8"nai",
        u8"nap",
        u8"nds",
        u8"new",
        u8"nia",
        u8"niu",
        u8"nog",
        u8"non",
        u8"nqo",
        u8"nso",
        u8"nub",
        u8"nwc",
        u8"nym",
        u8"nyn",
        u8"nyo",
        u8"nzi",
        u8"osa",
        u8"ota",
        u8"oto",
        u8"paa",
        u8"pag",
        u8"pal",
        u8"pam",
        u8"pap",
        u8"pau",
        u8"peo",
        u8"phi",
        u8"phn",
        u8"pon",
        u8"pra",
        u8"pro",
        u8"raj",
        u8"rap",
        u8"rar",
        u8"rom",
        u8"rup",
        u8"sad",
        u8"sah",
        u8"sai",
        u8"sal",
        u8"sam",
        u8"sas",
        u8"sat",
        u8"scn",
        u8"sco",
        u8"sel",
        u8"sga",
        u8"shn",
        u8"sid",
        u8"sio",
        u8"sma",
        u8"smj",
        u8"smn",
        u8"sms",
        u8"snk",
        u8"sog",
        u8"son",
        u8"srn",
        u8"srr",
        u8"suk",
        u8"sus",
        u8"sux",
        u8"syc",
        u8"syr",
        u8"tai",
        u8"tem",
        u8"ter",
        u8"tet",
        u8"tig",
        u8"tiv",
        u8"tkl",
        u8"tlh",
        u8"tli",
        u8"tmh",
        u8"tog",
        u8"tpi",
        u8"tsi",
        u8"tum",
        u8"tup",
        u8"tut",
        u8"tvl",
        u8"tyv",
        u8"udm",
        u8"uga",
        u8"umb",
        u8"vai",
        u8"vot",
        u8"wak",
        u8"wal",
        u8"war",
        u8"was",
        u8"wen",
        u8"xal",
        u8"yao",
        u8"yap",
        u8"ypk",
        u8"zap",
        u8"zbl",
        u8"zen",
        u8"zgh",
        u8"znd",
        u8"zun",
        u8"zza",
        u8"und"
    };
}

namespace omn
{
    constexpr const unicode::UTF8Character * ISO6391CodeString( ISO6391LanguageCode code )
    {
        return ISO6391CodeStrings[(code % ISO6391CodesCount)];
    }

    constexpr const unicode::UTF8Character * ISO6392CodeString( ISO6392LanguageCode code )
    {
        return ISO6392CodeStrings[((code >= ISO6392CodesCount) ? (ISO6392CodesCount - 1) : code)];
    }
}

namespace std
{
    inline string to_string( const omn::ISO6391LanguageCode code )
    {
        return omn::ISO6391CodeString(code);
    }

    inline ostream & operator << ( ostream & os, const omn::ISO6391LanguageCode code )
    {
        os << omn::ISO6391CodeString(code);
        return os;
    }

    inline string to_string( const omn::ISO6392LanguageCode code )
    {
        return omn::ISO6392CodeString(code);
    }

    inline ostream & operator << ( ostream & os, const omn::ISO6392LanguageCode code )
    {
        os << omn::ISO6392CodeString(code);
        return os;
    }
}

#endif // _OMN_ISO639_INCLUDED
