
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright (c) 2019 Pedro Vernetti G.
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
#ifndef _OMN_STOPWORDS_INCLUDED
#define _OMN_STOPWORDS_INCLUDED

#include "globalUtilities.hpp"
#include "ISO639.hpp"
#include "tokenization.hpp"
#include "unorderedMap.hpp"
#include "set.hpp"

namespace // internal parts
{
    constexpr const uint16_t countPerLanguage[omn::ISO6392LanguageCode::zza + 1] =
    {
        /*zxx*/ 0,
        /*aar*/ 0,   /*abk*/ 0,   /*afr*/ 0,   /*aka*/ 0,   /*alb*/ 0,   /*amh*/ 0,
        /*ara*/ 248, /*arg*/ 0,   /*arm*/ 0,   /*asm*/ 0,   /*ava*/ 0,   /*ave*/ 0,
        /*aym*/ 0,   /*aze*/ 164, /*bak*/ 0,   /*bam*/ 0,   /*baq*/ 0,   /*bel*/ 0,
        /*ben*/ 0,   /*bih*/ 0,   /*bis*/ 0,   /*bos*/ 0,   /*bre*/ 0,   /*bul*/ 0,
        /*bur*/ 0,   /*cat*/ 0,   /*cha*/ 0,   /*che*/ 0,   /*chi*/ 0,   /*chu*/ 0,
        /*chv*/ 0,   /*cor*/ 0,   /*cos*/ 0,   /*cre*/ 0,   /*cze*/ 0,   /*dan*/ 94,
        /*div*/ 0,   /*dut*/ 101, /*dzo*/ 0,   /*eng*/ 128, /*epo*/ 0,   /*est*/ 0,
        /*ewe*/ 0,   /*fao*/ 0,   /*fij*/ 0,   /*fin*/ 235, /*fre*/ 155, /*fry*/ 0,
        /*ful*/ 0,   /*geo*/ 0,   /*ger*/ 231, /*gla*/ 0,   /*gle*/ 109, /*glg*/ 0,
        /*glv*/ 0,   /*gre*/ 265, /*grn*/ 0,   /*guj*/ 0,   /*hat*/ 0,   /*hau*/ 0,
        /*heb*/ 0,   /*her*/ 0,   /*hin*/ 0,   /*hmo*/ 0,   /*hrv*/ 0,   /*hun*/ 199,
        /*ibo*/ 0,   /*ice*/ 0,   /*ido*/ 0,   /*iii*/ 0,   /*iku*/ 0,   /*ile*/ 0,
        /*ina*/ 0,   /*ind*/ 0,   /*ipk*/ 0,   /*ita*/ 279, /*jav*/ 0,   /*jpn*/ 0,
        /*kal*/ 0,   /*kan*/ 0,   /*kas*/ 0,   /*kau*/ 0,   /*kaz*/ 0,   /*khm*/ 0,
        /*kik*/ 0,   /*kin*/ 0,   /*kir*/ 0,   /*kom*/ 0,   /*kon*/ 0,   /*kor*/ 0,
        /*kua*/ 0,   /*kur*/ 0,   /*lao*/ 0,   /*lat*/ 0,   /*lav*/ 0,   /*lim*/ 0,
        /*lin*/ 0,   /*lit*/ 0,   /*ltz*/ 0,   /*lub*/ 0,   /*lug*/ 0,   /*mac*/ 0,
        /*mah*/ 0,   /*mal*/ 0,   /*mao*/ 0,   /*mar*/ 0,   /*may*/ 0,   /*mlg*/ 0,
        /*mlt*/ 0,   /*mon*/ 0,   /*nau*/ 0,   /*nav*/ 0,   /*nbl*/ 0,   /*nde*/ 0,
        /*ndo*/ 0,   /*nep*/ 0,   /*nor*/ 176, /*nya*/ 0,   /*oci*/ 0,   /*oji*/ 0,
        /*ori*/ 0,   /*orm*/ 0,   /*oss*/ 0,   /*pan*/ 0,   /*per*/ 0,   /*pli*/ 0,
        /*pol*/ 0,   /*por*/ 203, /*pus*/ 0,   /*que*/ 0,   /*roh*/ 0,   /*rum*/ 355,
        /*run*/ 0,   /*rus*/ 150, /*sag*/ 0,   /*san*/ 0,   /*sin*/ 0,   /*slo*/ 0,
        /*slv*/ 0,   /*sme*/ 0,   /*smo*/ 0,   /*sna*/ 0,   /*snd*/ 0,   /*som*/ 0,
        /*sot*/ 0,   /*spa*/ 315, /*srd*/ 0,   /*srp*/ 0,   /*ssw*/ 0,   /*sun*/ 0,
        /*swa*/ 0,   /*swe*/ 114, /*tah*/ 0,   /*tam*/ 0,   /*tat*/ 0,   /*tel*/ 0,
        /*tgk*/ 0,   /*tgl*/ 0,   /*tha*/ 0,   /*tib*/ 0,   /*tir*/ 0,   /*ton*/ 0,
        /*tsn*/ 0,   /*tso*/ 0,   /*tuk*/ 0,   /*tur*/ 53,  /*twi*/ 0,   /*uig*/ 0,
        /*ukr*/ 0,   /*urd*/ 0,   /*uzb*/ 0,   /*ven*/ 0,   /*vie*/ 201, /*vol*/ 0,
        /*wel*/ 0,   /*wln*/ 0,   /*wol*/ 0,   /*xho*/ 0,   /*yid*/ 0,   /*yor*/ 0,
        /*zha*/ 0,   /*zul*/ 0,   /*ace*/ 0,   /*ach*/ 0,   /*ada*/ 0,   /*ady*/ 0,
        /*afh*/ 0,   /*ain*/ 0,   /*akk*/ 0,   /*ale*/ 0,   /*alg*/ 0,   /*alt*/ 0,
        /*ang*/ 0,   /*anp*/ 0,   /*apa*/ 0,   /*arc*/ 0,   /*arn*/ 0,   /*arp*/ 0,
        /*arw*/ 0,   /*ast*/ 0,   /*ath*/ 0,   /*aus*/ 0,   /*awa*/ 0,   /*bad*/ 0,
        /*bai*/ 0,   /*bal*/ 0,   /*ban*/ 0,   /*bas*/ 0,   /*bej*/ 0,   /*bem*/ 0,
        /*ber*/ 0,   /*bho*/ 0,   /*bik*/ 0,   /*bin*/ 0,   /*bla*/ 0,   /*bra*/ 0,
        /*btk*/ 0,   /*bua*/ 0,   /*bug*/ 0,   /*byn*/ 0,   /*cad*/ 0,   /*cai*/ 0,
        /*car*/ 0,   /*ceb*/ 0,   /*chb*/ 0,   /*chg*/ 0,   /*chk*/ 0,   /*chm*/ 0,
        /*chn*/ 0,   /*cho*/ 0,   /*chp*/ 0,   /*chr*/ 0,   /*chy*/ 0,   /*cmc*/ 0,
        /*cnr*/ 0,   /*cop*/ 0,   /*cpe*/ 0,   /*cpf*/ 0,   /*cpp*/ 0,   /*crh*/ 0,
        /*csb*/ 0,   /*dak*/ 0,   /*dar*/ 0,   /*day*/ 0,   /*del*/ 0,   /*den*/ 0,
        /*dgr*/ 0,   /*din*/ 0,   /*doi*/ 0,   /*dsb*/ 0,   /*dua*/ 0,   /*dum*/ 0,
        /*dyu*/ 0,   /*efi*/ 0,   /*egy*/ 0,   /*eka*/ 0,   /*elx*/ 0,   /*enm*/ 0,
        /*ewo*/ 0,   /*fan*/ 0,   /*fat*/ 0,   /*fon*/ 0,   /*frm*/ 0,   /*fro*/ 0,
        /*frr*/ 0,   /*frs*/ 0,   /*fur*/ 0,   /*gaa*/ 0,   /*gay*/ 0,   /*gba*/ 0,
        /*gez*/ 0,   /*gil*/ 0,   /*gmh*/ 0,   /*goh*/ 0,   /*gon*/ 0,   /*gor*/ 0,
        /*got*/ 0,   /*grb*/ 0,   /*grc*/ 0,   /*gsw*/ 0,   /*gwi*/ 0,   /*hai*/ 0,
        /*haw*/ 0,   /*hil*/ 0,   /*him*/ 0,   /*hit*/ 0,   /*hmn*/ 0,   /*hsb*/ 0,
        /*hup*/ 0,   /*iba*/ 0,   /*ijo*/ 0,   /*ilo*/ 0,   /*inh*/ 0,   /*iro*/ 0,
        /*jbo*/ 0,   /*jpr*/ 0,   /*jrb*/ 0,   /*kaa*/ 0,   /*kab*/ 0,   /*kac*/ 0,
        /*kam*/ 0,   /*kar*/ 0,   /*kaw*/ 0,   /*kbd*/ 0,   /*kha*/ 0,   /*khi*/ 0,
        /*kho*/ 0,   /*kmb*/ 0,   /*kok*/ 0,   /*kos*/ 0,   /*kpe*/ 0,   /*krc*/ 0,
        /*krl*/ 0,   /*kro*/ 0,   /*kru*/ 0,   /*kum*/ 0,   /*kut*/ 0,   /*lad*/ 0,
        /*lah*/ 0,   /*lam*/ 0,   /*lez*/ 0,   /*lol*/ 0,   /*loz*/ 0,   /*lua*/ 0,
        /*lui*/ 0,   /*lun*/ 0,   /*luo*/ 0,   /*lus*/ 0,   /*mad*/ 0,   /*mag*/ 0,
        /*mai*/ 0,   /*mak*/ 0,   /*man*/ 0,   /*mas*/ 0,   /*mdf*/ 0,   /*mdr*/ 0,
        /*men*/ 0,   /*mga*/ 0,   /*mic*/ 0,   /*min*/ 0,   /*mis*/ 0,   /*mkh*/ 0,
        /*mnc*/ 0,   /*mni*/ 0,   /*mno*/ 0,   /*moh*/ 0,   /*mos*/ 0,   /*mul*/ 0,
        /*mun*/ 0,   /*mus*/ 0,   /*mwl*/ 0,   /*mwr*/ 0,   /*myn*/ 0,   /*myv*/ 0,
        /*nah*/ 0,   /*nai*/ 0,   /*nap*/ 0,   /*nds*/ 0,   /*new*/ 0,   /*nia*/ 0,
        /*niu*/ 0,   /*nog*/ 0,   /*non*/ 0,   /*nqo*/ 0,   /*nso*/ 0,   /*nub*/ 0,
        /*nwc*/ 0,   /*nym*/ 0,   /*nyn*/ 0,   /*nyo*/ 0,   /*nzi*/ 0,   /*osa*/ 0,
        /*ota*/ 0,   /*oto*/ 0,   /*paa*/ 0,   /*pag*/ 0,   /*pal*/ 0,   /*pam*/ 0,
        /*pap*/ 0,   /*pau*/ 0,   /*peo*/ 0,   /*phi*/ 0,   /*phn*/ 0,   /*pon*/ 0,
        /*pra*/ 0,   /*pro*/ 0,   /*raj*/ 0,   /*rap*/ 0,   /*rar*/ 0,   /*rom*/ 0,
        /*rup*/ 0,   /*sad*/ 0,   /*sah*/ 0,   /*sai*/ 0,   /*sal*/ 0,   /*sam*/ 0,
        /*sas*/ 0,   /*sat*/ 0,   /*scn*/ 0,   /*sco*/ 0,   /*sel*/ 0,   /*sga*/ 0,
        /*shn*/ 0,   /*sid*/ 0,   /*sio*/ 0,   /*sma*/ 0,   /*smj*/ 0,   /*smn*/ 0,
        /*sms*/ 0,   /*snk*/ 0,   /*sog*/ 0,   /*son*/ 0,   /*srn*/ 0,   /*srr*/ 0,
        /*suk*/ 0,   /*sus*/ 0,   /*sux*/ 0,   /*syc*/ 0,   /*syr*/ 0,   /*tai*/ 0,
        /*tem*/ 0,   /*ter*/ 0,   /*tet*/ 0,   /*tig*/ 0,   /*tiv*/ 0,   /*tkl*/ 0,
        /*tlh*/ 0,   /*tli*/ 0,   /*tmh*/ 0,   /*tog*/ 0,   /*tpi*/ 0,   /*tsi*/ 0,
        /*tum*/ 0,   /*tup*/ 0,   /*tut*/ 0,   /*tvl*/ 0,   /*tyv*/ 0,   /*udm*/ 0,
        /*uga*/ 0,   /*umb*/ 0,   /*vai*/ 0,   /*vot*/ 0,   /*wak*/ 0,   /*wal*/ 0,
        /*war*/ 0,   /*was*/ 0,   /*wen*/ 0,   /*xal*/ 0,   /*yao*/ 0,   /*yap*/ 0,
        /*ypk*/ 0,   /*zap*/ 0,   /*zbl*/ 0,   /*zen*/ 0,   /*zgh*/ 0,   /*znd*/ 0,
        /*zun*/ 0,   /*zza*/ 0
    };

    constexpr const omn::unicode::UTF32Character * ara[248] = // Arabic
    {
        U"إذ", U"إذا", U"إذما", U"إذن", U"أف", U"أقل", U"أكثر", U"ألا", U"إلا",
        U"التي", U"الذي", U"الذين", U"اللاتي", U"اللائي", U"اللتان", U"اللتيا",
        U"اللتين",U"اللذان", U"اللذين", U"اللواتي", U"إلى", U"إليك", U"إليكم",
        U"إليكما", U"إليكن", U"أم", U"أما", U"أما", U"إما", U"أن", U"إن", U"إنا",
        U"أنا", U"أنت", U"أنتم", U"أنتما", U"أنتن", U"إنما", U"إنه", U"أنى", U"أنى",
        U"آه", U"آها", U"أو", U"أولاء", U"أولئك", U"أوه", U"آي", U"أي", U"أيها",
        U"إي", U"أين", U"أين", U"أينما", U"إيه", U"بخ", U"بس", U"بعد", U"بعض",
        U"بك", U"بكم", U"بكم", U"بكما", U"بكن", U"بل", U"بلى", U"بما", U"بماذا",
        U"بمن", U"بنا", U"به", U"بها", U"بهم", U"بهما", U"بهن", U"بي", U"بين",
        U"بيد", U"تلك", U"تلكم", U"تلكما", U"ته", U"تي", U"تين", U"تينك", U"ثم",
        U"ثمة", U"حاشا", U"حبذا", U"حتى", U"حيث", U"حيثما", U"حين", U"خلا",
        U"دون", U"ذا", U"ذات", U"ذاك", U"ذان", U"ذانك", U"ذلك", U"ذلكم", U"ذلكما",
        U"ذلكن", U"ذه", U"ذو", U"ذوا", U"ذواتا", U"ذواتي", U"ذي", U"ذين", U"ذينك",
        U"ريث", U"سوف", U"سوى", U"شتان", U"عدا", U"عسى", U"عل", U"على", U"عليك",
        U"عليه", U"عما", U"عن", U"عند", U"غير", U"فإذا", U"فإن", U"فلا", U"فمن",
        U"في", U"فيم", U"فيما", U"فيه", U"فيها", U"قد", U"كأن", U"كأنما", U"كأي",
        U"كأين", U"كذا", U"كذلك", U"كل", U"كلا", U"كلاهما", U"كلتا", U"كلما",U"كليكما",
        U"كليهما", U"كم", U"كم", U"كما", U"كي", U"كيت", U"كيف", U"كيفما", U"لا",
        U"لاسيما", U"لدى", U"لست", U"لستم", U"لستما", U"لستن", U"لسن", U"لسنا",
        U"لعل", U"لك", U"لكم", U"لكما", U"لكن", U"لكنما", U"لكي", U"لكيلا", U"لم",
        U"لما", U"لن", U"لنا", U"له", U"لها", U"لهم", U"لهما", U"لهن", U"لو",
        U"لولا", U"لوما", U"لي", U"لئن", U"ليت", U"ليس", U"ليسا", U"ليست", U"ليستا",
        U"ليسوا", U"ما", U"ماذا", U"متى", U"مذ", U"مع", U"مما", U"ممن", U"من", U"منه",
        U"منها", U"منذ", U"مه", U"مهما", U"نحن", U"نحو", U"نعم", U"ها", U"هاتان",
        U"هاته", U"هاتي", U"هاتين", U"هاك", U"هاهنا", U"هذا", U"هذان", U"هذه", U"هذي",
        U"هذين", U"هكذا", U"هل", U"هلا", U"هم", U"هما", U"هن", U"هنا", U"هناك",
        U"هنالك", U"هو", U"هؤلاء", U"هي", U"هيا", U"هيت", U"هيهات", U"والذي",U"والذين",
        U"وإذ", U"وإذا", U"وإن", U"ولا", U"ولكن", U"ولو", U"وما", U"ومن", U"وهو", U"يا"
    };

    constexpr const omn::unicode::UTF32Character * aze[165] = // Azerbaijani
    {
        U"a", U"ad", U"altı", U"altmış", U"amma", U"arasında", U"artıq", U"ay",
        U"az", U"bax", U"belə", U"bəli", U"bəlkə", U"beş", U"bəy", U"bəzən",
        U"bəzi", U"bilər", U"bir", U"biraz", U"biri", U"birşey", U"biz", U"bizim",
        U"bizlər", U"bu", U"buna", U"bundan", U"bunların", U"bunu", U"bunun",
        U"buradan", U"bütün", U"ci", U"cı", U"çox", U"cu", U"cü", U"çünki", U"da",
        U"daha", U"də", U"dedi", U"dək", U"dən", U"dəqiqə", U"deyil", U"dir",
        U"doqquz", U"doqsan", U"dörd", U"düz", U"ə", U"edən", U"edir", U"əgər",
        U"əlbəttə", U"elə", U"əlli", U"ən", U"əslində", U"et", U"etdi", U"etmə",
        U"etmək", U"faiz", U"gilə", U"görə", U"ha", U"haqqında", U"harada", U"hə",
        U"heç", U"həm", U"həmin", U"həmişə", U"hər", U"ı", U"idi", U"iki", U"il",
        U"ildə", U"ilə", U"ilk", U"in", U"indi", U"isə", U"istifadə", U"iyirmi",
        U"ki", U"kim", U"kimə", U"kimi", U"lakin", U"lap", U"məhz", U"mən", U"mənə",
        U"mirşey", U"nə", U"nəhayət", U"niyə", U"o", U"obirisi", U"of", U"olan",
        U"olar", U"olaraq", U"oldu", U"olduğu", U"olmadı", U"olmaz", U"olmuşdur",
        U"olsun", U"olur", U"on", U"ona", U"ondan", U"onlar", U"onlardan", U"onların",
        U"onsuzda", U"onu", U"onun", U"oradan", U"otuz", U"öz", U"özü", U"qarşı",
        U"qədər", U"qırx", U"saat", U"sadəcə", U"saniyə", U"səhv", U"səkkiz",
        U"səksən", U"sən", U"sənə", U"sənin", U"siz", U"sizin", U"sizlər", U"sonra",
        U"təəssüf", U"ü", U"üç", U"üçün", U"var", U"və", U"xan", U"xanım", U"xeyr",
        U"ya", U"yalnız", U"yaxşı", U"yeddi", U"yenə", U"yəni", U"yetmiş", U"yox",
        U"yoxdur", U"yoxsa", U"yüz", U"zaman"
    };

    constexpr const omn::unicode::UTF32Character * dan[94] = // Danish
    {
        U"ad", U"af", U"alle", U"alt", U"anden", U"at", U"blev", U"blive",
        U"bliver", U"da", U"de", U"dem", U"den", U"denne", U"der",
        U"deres", U"det", U"dette", U"dig", U"din", U"disse", U"dog", U"du",
        U"efter", U"eller", U"en", U"end", U"er", U"et", U"for", U"fra",
        U"ham", U"han", U"hans", U"har", U"havde", U"have", U"hende",
        U"hendes", U"her", U"hos", U"hun", U"hvad", U"hvis", U"hvor", U"i",
        U"ikke", U"ind", U"jeg", U"jer", U"jo", U"kunne", U"man", U"mange",
        U"med", U"meget", U"men", U"mig", U"min", U"mine", U"mit", U"mod",
        U"når", U"ned", U"noget", U"nogle", U"nu", U"og", U"også", U"om",
        U"op", U"os", U"over", U"på", U"sådan", U"selv", U"sig", U"sin",
        U"sine", U"sit", U"skal", U"skulle", U"som", U"thi", U"til", U"ud",
        U"under", U"være", U"været", U"var", U"vi", U"vil", U"ville", U"vor"
    };

    constexpr const omn::unicode::UTF32Character * dut[101] = // Dutch
    {
        U"de", U"en", U"van", U"ik", U"te", U"dat", U"die", U"in", U"een", U"hij",
        U"het", U"niet", U"zijn", U"is", U"was", U"op", U"aan", U"met", U"als",
        U"voor", U"had", U"er", U"maar", U"om", U"hem", U"dan", U"zou", U"of",
        U"wat", U"mijn", U"men", U"dit", U"zo", U"door", U"over", U"ze", U"zich",
        U"bij", U"ook", U"tot", U"je", U"mij", U"uit", U"der", U"daar", U"haar",
        U"naar", U"heb", U"hoe", U"heeft", U"hebben", U"deze", U"u", U"want",
        U"nog", U"zal", U"me", U"zij", U"nu", U"ge", U"geen", U"omdat", U"iets",
        U"worden", U"toch", U"al", U"waren", U"veel", U"meer", U"doen", U"toen",
        U"moet", U"ben", U"zonder", U"kan", U"hun", U"dus", U"alles", U"onder",
        U"ja", U"eens", U"hier", U"wie", U"werd", U"altijd", U"doch", U"wordt",
        U"wezen", U"kunnen", U"ons", U"zelf", U"tegen", U"na", U"reeds", U"wil",
        U"kon", U"niets", U"uw", U"iemand", U"geweest", U"andere"
    };

    constexpr const omn::unicode::UTF32Character * eng[128] = // English
    {
        U"a", U"about", U"above", U"after", U"again", U"against", U"all", U"am",
        U"an", U"and", U"any", U"are", U"as", U"at", U"be", U"because", U"been",
        U"before", U"being", U"below", U"between", U"both", U"but", U"by", U"can",
        U"did", U"do", U"does", U"doing", U"don", U"down", U"during", U"each",
        U"few", U"for", U"from", U"further", U"had", U"has", U"have", U"having",
        U"he", U"her", U"here", U"hers", U"herself", U"him", U"himself", U"his",
        U"how", U"i", U"if", U"in", U"into", U"is", U"it", U"its", U"itself",
        U"just", U"m", U"me", U"more", U"most", U"my", U"myself", U"no", U"nor",
        U"not", U"now", U"of", U"off",U"on", U"once", U"only", U"or", U"other",
        U"our", U"ours", U"ourselves", U"out", U"over", U"own", U"s", U"same",
        U"she", U"should", U"so", U"some", U"such", U"t", U"than", U"that",
        U"the", U"their", U"theirs", U"them", U"themselves", U"then", U"there",
        U"these", U"they", U"this", U"those", U"through", U"to", U"too", U"under",
        U"until", U"up", U"very", U"was", U"we", U"were", U"what", U"when",
        U"where", U"which", U"while", U"who", U"whom", U"why", U"will", U"with",
        U"you", U"your", U"yours", U"yourself", U"yourselves"
    };

    constexpr const omn::unicode::UTF32Character * fin[235] = // Finnish
    {
        U"olla", U"olen", U"olet", U"on", U"olemme", U"olette", U"ovat", U"ole",
        U"oli", U"olisi", U"olisit", U"olisin", U"olisimme", U"olisitte",
        U"olisivat", U"olit", U"olin", U"olimme", U"olitte", U"olivat", U"ollut",
        U"olleet", U"en", U"et", U"ei", U"emme", U"ette", U"eivät", U"minä",
        U"minun", U"minut", U"minua", U"minussa", U"minusta", U"minuun", U"minulla",
        U"minulta", U"minulle", U"sinä", U"sinun", U"sinut", U"sinua", U"sinussa",
        U"sinusta", U"sinuun", U"sinulla", U"sinulta", U"sinulle", U"hän", U"hänen",
        U"hänet", U"häntä", U"hänessä", U"hänestä", U"häneen", U"hänellä",
        U"häneltä", U"hänelle", U"me", U"meidän", U"meidät", U"meitä", U"meissä",
        U"meistä", U"meihin", U"meillä", U"meiltä", U"meille", U"te", U"teidän",
        U"teidät", U"teitä", U"teissä", U"teistä", U"teihin", U"teillä", U"teiltä",
        U"teille", U"he", U"heidän", U"heidät", U"heitä", U"heissä", U"heistä",
        U"heihin", U"heillä", U"heiltä", U"heille", U"tämä", U"tämän", U"tätä",
        U"tässä", U"tästä", U"tähän", U"tallä", U"tältä", U"tälle", U"tänä",
        U"täksi", U"tuo", U"tuon", U"tuotä", U"tuossa", U"tuosta", U"tuohon",
        U"tuolla", U"tuolta", U"tuolle", U"tuona", U"tuoksi", U"se", U"sen",
        U"sitä",U"siinä", U"siitä", U"siihen", U"sillä", U"siltä", U"sille", U"sinä",
        U"siksi", U"nämä", U"näiden", U"näitä", U"näissä", U"näistä", U"näihin",
        U"näillä", U"näiltä", U"näille", U"näinä", U"näiksi", U"nuo", U"noiden",
        U"noita", U"noissa", U"noista", U"noihin", U"noilla", U"noilta", U"noille",
        U"noina", U"noiksi", U"ne", U"niiden", U"niitä", U"niissä", U"niistä",
        U"niihin", U"niillä", U"niiltä", U"niille", U"niinä", U"niiksi", U"kuka",
        U"kenen", U"kenet", U"ketä", U"kenessä", U"kenestä", U"keneen", U"kenellä",
        U"keneltä", U"kenelle", U"kenenä", U"keneksi", U"ketkä", U"keiden", U"ketkä",
        U"keitä", U"keissä", U"keistä", U"keihin", U"keillä", U"keiltä", U"keille",
        U"keinä", U"keiksi", U"mikä", U"minkä", U"minkä", U"mitä", U"missä",
        U"mistä", U"mihin", U"millä", U"miltä", U"mille", U"minä", U"miksi",
        U"mitkä", U"joka", U"jonka", U"jota", U"jossa", U"josta", U"johon", U"jolla",
        U"jolta", U"jolle", U"jona", U"joksi", U"jotka", U"joiden", U"joita",
        U"joissa", U"joista", U"joihin", U"joilla", U"joilta", U"joille", U"joina",
        U"joiksi", U"että", U"ja", U"jos", U"koska", U"kuin", U"mutta", U"niin",
        U"sekä", U"sillä", U"tai", U"vaan", U"vai", U"vaikka", U"kanssa", U"mukaan",
        U"noin", U"poikki", U"yli", U"kun", U"niin", U"nyt", U"itse"
    };

    constexpr const omn::unicode::UTF32Character * fre[155] = // French
    {
        U"au", U"aux", U"avec", U"ce", U"ces", U"dans", U"de", U"des", U"du",
        U"elle", U"en", U"et", U"eux", U"il", U"je", U"la", U"le", U"leur",
        U"lui", U"ma", U"mais", U"me", U"même", U"mes", U"moi", U"mon", U"ne",
        U"nos", U"notre", U"nous", U"on", U"ou", U"par", U"pas", U"pour", U"qu",
        U"que", U"qui", U"sa", U"se", U"ses", U"son", U"sur", U"ta", U"te",
        U"tes", U"toi", U"ton", U"tu", U"un", U"une", U"vos", U"votre", U"vous",
        U"c", U"d", U"j", U"l", U"à", U"m", U"n", U"s", U"t", U"y", U"été",
        U"étée", U"étées", U"étés", U"étant", U"étante", U"étants", U"étantes",
        U"suis", U"es", U"est", U"sommes", U"êtes", U"sont", U"serai", U"seras",
        U"sera", U"serons", U"serez", U"seront", U"serais", U"serait", U"serions",
        U"seriez", U"seraient", U"étais", U"était", U"étions", U"étiez", U"étaient",
        U"fus", U"fut", U"fûmes", U"fûtes", U"furent", U"sois", U"soit", U"soyons",
        U"soyez", U"soient", U"fusse", U"fusses", U"fût", U"fussions", U"fussiez",
        U"fussent", U"ayant", U"ayante", U"ayantes", U"ayants", U"eu", U"eue",
        U"eues", U"eus", U"ai", U"as", U"avons", U"avez", U"ont", U"aurai",
        U"auras", U"aura", U"aurons", U"aurez", U"auront", U"aurais", U"aurait",
        U"aurions", U"auriez", U"auraient", U"avais", U"avait", U"avions", U"aviez",
        U"avaient", U"eut", U"eûmes", U"eûtes", U"eurent", U"aie", U"aies", U"ait",
        U"ayons", U"ayez", U"aient", U"eusse", U"eusses", U"eût", U"eussions",
        U"eussiez", U"eussent"
    };

    constexpr const omn::unicode::UTF32Character * ger[231] = // German
    {
        U"aber", U"alle", U"allem", U"allen", U"aller", U"alles", U"als", U"also",
        U"am", U"an", U"ander", U"andere", U"anderem", U"anderen", U"anderer",
        U"anderes", U"anderm", U"andern", U"anderr", U"anders", U"auch", U"auf",
        U"aus", U"bei", U"bin", U"bis", U"bist", U"da", U"damit", U"dann", U"der",
        U"den", U"des", U"dem", U"die", U"das", U"daß", U"derselbe", U"derselben",
        U"denselben", U"desselben", U"demselben", U"dieselbe", U"dieselben",
        U"dasselbe", U"dazu", U"dein", U"deine", U"deinem", U"deinen", U"deiner",
        U"deines", U"denn", U"derer", U"dessen", U"dich", U"dir", U"du", U"dies",
        U"diese", U"diesem", U"diesen", U"dieser", U"dieses", U"doch", U"dort",
        U"durch", U"ein", U"eine", U"einem", U"einen", U"einer", U"eines",
        U"einig", U"einige", U"einigem", U"einigen", U"einiger", U"einiges",
        U"einmal", U"er", U"ihn", U"ihm", U"es", U"etwas", U"euer", U"eure",
        U"eurem", U"euren", U"eurer", U"eures", U"für", U"gegen", U"gewesen",
        U"hab", U"habe", U"haben", U"hat", U"hatte", U"hatten", U"hier", U"hin",
        U"hinter", U"ich", U"mich", U"mir", U"ihr", U"ihre", U"ihrem", U"ihren",
        U"ihrer", U"ihres", U"euch", U"im", U"in", U"indem", U"ins", U"ist",
        U"jede", U"jedem", U"jeden", U"jeder", U"jedes", U"jene", U"jenem",
        U"jenen", U"jener", U"jenes", U"jetzt", U"kann", U"kein", U"keine",
        U"keinem", U"keinen", U"keiner", U"keines", U"können", U"könnte", U"machen",
        U"man", U"manche", U"manchem", U"manchen", U"mancher", U"manches", U"mein",
        U"meine", U"meinem", U"meinen", U"meiner", U"meines", U"mit", U"muss",
        U"musste", U"nach", U"nicht", U"nichts", U"noch", U"nun", U"nur", U"ob",
        U"oder", U"ohne", U"sehr", U"sein", U"seine", U"seinem", U"seinen",
        U"seiner", U"seines", U"selbst", U"sich", U"sie", U"ihnen", U"sind",
        U"so", U"solche", U"solchem", U"solchen", U"solcher", U"solches", U"soll",
        U"sollte", U"sondern", U"sonst", U"über", U"um", U"und", U"uns", U"unsere",
        U"unserem", U"unseren", U"unser", U"unseres", U"unter", U"viel", U"vom",
        U"von", U"vor", U"während", U"war", U"waren", U"warst", U"was", U"weg",
        U"weil", U"weiter", U"welche", U"welchem", U"welchen", U"welcher",
        U"welches", U"wenn", U"werde", U"werden", U"wie", U"wieder", U"will",
        U"wir", U"wird", U"wirst", U"wo", U"wollen", U"wollte", U"würde",
        U"würden", U"zu", U"zum", U"zur", U"zwar", U"zwischen"
    };

    constexpr const omn::unicode::UTF32Character * gle[109] = // Irish
    {
        U"a", U"ach", U"ag", U"agus", U"an", U"aon", U"ar", U"arna", U"as", U"b",
        U"ba", U"beirt", U"bhúr", U"caoga", U"ceathair", U"ceathrar", U"chomh",
        U"chtó", U"chuig", U"chun", U"cois", U"céad", U"cúig", U"cúigear", U"d",
        U"daichead", U"dar", U"de", U"deich", U"deichniúr", U"den", U"dhá", U"do",
        U"don", U"dtí", U"dá", U"dár", U"dó", U"faoi", U"faoin", U"faoina",
        U"faoinár", U"fara", U"fiche", U"gach", U"gan", U"go", U"gur", U"haon",
        U"hocht", U"i", U"iad", U"idir", U"in", U"ina", U"ins", U"inár", U"is",
        U"le", U"leis", U"lena", U"lenár", U"m'", U"mar", U"mo", U"mé", U"na",
        U"nach", U"naoi", U"naonúr", U"ná", U"ní", U"níor", U"nó", U"nócha",
        U"ocht", U"ochtar", U"os", U"roimh", U"sa", U"seacht", U"seachtar",
        U"seachtó", U"seasca", U"seisear", U"siad", U"sibh", U"sinn", U"sna",
        U"sé", U"sí", U"tar", U"thar", U"thú", U"triúr", U"trí", U"trína",
        U"trínár", U"tríocha", U"tú", U"um", U"ár", U"é", U"éis", U"í", U"ó",
        U"ón", U"óna", U"ónár"
    };

    constexpr const omn::unicode::UTF32Character * gre[265] = // Greek
    {
        U"αλλα", U"αν", U"αντι", U"απο", U"αυτα", U"αυτεσ", U"αυτη", U"αυτο",
        U"αυτοι", U"αυτοσ", U"αυτουσ", U"αυτων", U"αἱ", U"αἳ", U"αἵ", U"αὐτόσ",
        U"αὐτὸς", U"αὖ", U"γάρ", U"γα", U"γα^", U"γε", U"για", U"γοῦν", U"γὰρ",
        U"δ'", U"δέ", U"δή", U"δαί", U"δαίσ", U"δαὶ", U"δαὶς", U"δε", U"δεν",
        U"δι'", U"διά", U"διὰ", U"δὲ", U"δὴ", U"δ’", U"εαν", U"ειμαι", U"ειμαστε",
        U"ειναι", U"εισαι", U"ειστε", U"εκεινα", U"εκεινεσ", U"εκεινη", U"εκεινο",
        U"εκεινοι", U"εκεινοσ", U"εκεινουσ", U"εκεινων", U"ενω", U"επ", U"επι", U"εἰ",
        U"εἰμί", U"εἰμὶ", U"εἰς", U"εἰσ", U"εἴ", U"εἴμι", U"εἴτε", U"η", U"θα",
        U"ισωσ", U"κ", U"καί", U"καίτοι", U"καθ", U"και", U"κατ", U"κατά", U"κατα",
        U"κατὰ", U"καὶ", U"κι", U"κἀν", U"κἂν", U"μέν", U"μή", U"μήτε", U"μα",
        U"με", U"μεθ", U"μετ", U"μετά", U"μετα", U"μετὰ", U"μη", U"μην", U"μἐν",
        U"μὲν", U"μὴ", U"μὴν", U"να", U"ο", U"οι", U"ομωσ", U"οπωσ", U"οσο", U"οτι",
        U"οἱ", U"οἳ", U"οἷς", U"οὐ", U"οὐδ", U"οὐδέ", U"οὐδείσ", U"οὐδεὶς", U"οὐδὲ",
        U"οὐδὲν", U"οὐκ", U"οὐχ", U"οὐχὶ", U"οὓς", U"οὔτε", U"οὕτω", U"οὕτως",
        U"οὕτωσ", U"οὖν", U"οὗ", U"οὗτος", U"οὗτοσ", U"παρ", U"παρά", U"παρα",
        U"παρὰ", U"περί", U"περὶ", U"ποια", U"ποιεσ", U"ποιο", U"ποιοι", U"ποιοσ",
        U"ποιουσ", U"ποιων", U"ποτε", U"που", U"ποῦ", U"προ", U"προσ", U"πρόσ",
        U"πρὸ", U"πρὸς", U"πως", U"πωσ", U"σε", U"στη", U"στην", U"στο", U"στον",
        U"σόσ", U"σύ", U"σύν", U"σὸς", U"σὺ", U"σὺν", U"τά", U"τήν", U"τί", U"τίς",
        U"τίσ", U"τα", U"ταῖς", U"τε", U"την", U"τησ", U"τι", U"τινα", U"τις",
        U"τισ", U"το", U"τοί", U"τοι", U"τοιοῦτος", U"τοιοῦτοσ", U"τον", U"τοτε",
        U"του", U"τούσ", U"τοὺς", U"τοῖς", U"τοῦ", U"των", U"τό", U"τόν", U"τότε",
        U"τὰ", U"τὰς", U"τὴν", U"τὸ", U"τὸν", U"τῆς", U"τῆσ", U"τῇ", U"τῶν", U"τῷ",
        U"ωσ", U"ἀλλ'", U"ἀλλά", U"ἀλλὰ", U"ἀλλ’", U"ἀπ", U"ἀπό", U"ἀπὸ", U"ἀφ",
        U"ἂν", U"ἃ", U"ἄλλος", U"ἄλλοσ", U"ἄν", U"ἄρα", U"ἅμα", U"ἐάν", U"ἐγώ",
        U"ἐγὼ", U"ἐκ", U"ἐμόσ", U"ἐμὸς", U"ἐν", U"ἐξ", U"ἐπί", U"ἐπεὶ", U"ἐπὶ",
        U"ἐστι", U"ἐφ", U"ἐὰν", U"ἑαυτοῦ", U"ἔτι", U"ἡ", U"ἢ", U"ἣ", U"ἤ", U"ἥ",
        U"ἧς", U"ἵνα", U"ὁ", U"ὃ", U"ὃν", U"ὃς", U"ὅ", U"ὅδε", U"ὅθεν", U"ὅπερ",
        U"ὅς", U"ὅσ", U"ὅστις", U"ὅστισ", U"ὅτε", U"ὅτι", U"ὑμόσ", U"ὑπ", U"ὑπέρ",
        U"ὑπό", U"ὑπὲρ", U"ὑπὸ", U"ὡς", U"ὡσ", U"ὥς", U"ὥστε", U"ὦ", U"ᾧ"
    };

    constexpr const omn::unicode::UTF32Character * hun[199] = // Hungarian
    {
        U"a", U"ahogy", U"ahol", U"aki", U"akik", U"akkor", U"alatt", U"által",
        U"általában", U"amely", U"amelyek", U"amelyekben", U"amelyeket", U"amelyet",
        U"amelynek", U"ami", U"amit", U"amolyan", U"amíg", U"amikor", U"át",
        U"abban", U"ahhoz", U"annak", U"arra", U"arról", U"az", U"azok", U"azon",
        U"azt", U"azzal", U"azért", U"aztán", U"azután", U"azonban", U"bár", U"be",
        U"belül", U"benne", U"cikk", U"cikkek", U"cikkeket", U"csak", U"de", U"e",
        U"eddig", U"egész", U"egy", U"egyes", U"egyetlen", U"egyéb", U"egyik",
        U"egyre", U"ekkor", U"el", U"elég", U"ellen", U"elõ", U"elõször", U"elõtt",
        U"elsõ", U"én", U"éppen", U"ebben", U"ehhez", U"emilyen", U"ennek", U"erre",
        U"ez", U"ezt", U"ezek", U"ezen", U"ezzel", U"ezért", U"és", U"fel", U"felé",
        U"hanem", U"hiszen", U"hogy", U"hogyan", U"igen", U"így", U"illetve",
        U"ill.", U"ill", U"ilyen", U"ilyenkor", U"ison", U"ismé", U"itt", U"jó",
        U"jól", U"jobban", U"kell", U"kellett", U"keresztül", U"keressünk", U"ki",
        U"kívül", U"között", U"közül", U"legalább", U"lehet", U"lehetett", U"legyen",
        U"lenne", U"lenni", U"lesz", U"lett", U"maga", U"magát", U"majd", U"majd",
        U"már", U"más", U"másik", U"meg", U"még", U"mellett", U"mert", U"mely",
        U"melyek", U"mi", U"mit", U"míg", U"miért", U"milyen", U"mikor", U"minden",
        U"mindent", U"mindenki", U"mindig", U"mint", U"mintha", U"mivel", U"most",
        U"nagy", U"nagyobb", U"nagyon", U"ne", U"néha", U"nekem", U"neki", U"nem",
        U"néhány", U"nélkül", U"nincs", U"olyan", U"ott", U"össze", U"õ", U"õk",
        U"õket", U"pedig", U"persze", U"rá", U"s", U"saját", U"sem", U"semmi",
        U"sok", U"sokat", U"sokkal", U"számára", U"szemben", U"szerint", U"szinte",
        U"talán", U"tehát", U"teljes", U"tovább", U"továbbá", U"több", U"úgy",
        U"ugyanis", U"új", U"újabb", U"újra", U"után", U"utána", U"utolsó", U"vagy",
        U"vagyis", U"valaki", U"valami", U"valamint", U"való", U"vagyok", U"van",
        U"vannak", U"volt", U"voltam", U"voltak", U"voltunk", U"vissza", U"vele",
        U"viszont", U"volna"
    };

    constexpr const omn::unicode::UTF32Character * ita[279] = // Italian
    {
        U"ad", U"al", U"allo", U"ai", U"agli", U"all", U"agl", U"alla", U"alle",
        U"con", U"col", U"coi", U"da", U"dal", U"dallo", U"dai", U"dagli",
        U"dall", U"dagl", U"dalla", U"dalle", U"di", U"del", U"dello", U"dei",
        U"degli", U"dell", U"degl", U"della", U"delle", U"in", U"nel", U"nello",
        U"nei", U"negli", U"nell", U"negl", U"nella", U"nelle", U"su", U"sul",
        U"sullo", U"sui", U"sugli", U"sull", U"sugl", U"sulla", U"sulle", U"per",
        U"tra", U"contro", U"io", U"tu", U"lui", U"lei", U"noi", U"voi",
        U"loro", U"mio", U"mia", U"miei", U"mie", U"tuo", U"tua", U"tuoi",
        U"tue", U"suo", U"sua", U"suoi", U"sue", U"nostro", U"nostra", U"nostri",
        U"nostre", U"vostro", U"vostra", U"vostri", U"vostre", U"mi", U"ti",
        U"ci", U"vi", U"lo", U"la", U"li", U"le", U"gli", U"ne", U"il", U"un",
        U"uno", U"una", U"ma", U"ed", U"se", U"perché", U"anche", U"come",
        U"dov", U"dove", U"che", U"chi", U"cui", U"non", U"più", U"quale",
        U"quanto", U"quanti", U"quanta", U"quante", U"quello", U"quelli",
        U"quella", U"quelle", U"questo", U"questi", U"questa", U"queste", U"si",
        U"tutto", U"tutti", U"a", U"c", U"e", U"i", U"l", U"o", U"ho", U"hai",
        U"ha", U"abbiamo", U"avete", U"hanno", U"abbia", U"abbiate", U"abbiano",
        U"avrò", U"avrai", U"avrà", U"avremo", U"avrete", U"avranno", U"avrei",
        U"avresti", U"avrebbe", U"avremmo", U"avreste", U"avrebbero", U"avevo",
        U"avevi", U"aveva", U"avevamo", U"avevate", U"avevano", U"ebbi",
        U"avesti", U"ebbe", U"avemmo", U"aveste", U"ebbero", U"avessi",
        U"avesse", U"avessimo", U"avessero", U"avendo", U"avuto", U"avuta",
        U"avuti", U"avute", U"sono", U"sei", U"è", U"siamo", U"siete", U"sia",
        U"siate", U"siano", U"sarò", U"sarai", U"sarà", U"saremo", U"sarete",
        U"saranno", U"sarei", U"saresti", U"sarebbe", U"saremmo", U"sareste",
        U"sarebbero", U"ero", U"eri", U"era", U"eravamo", U"eravate", U"erano",
        U"fui", U"fosti", U"fu", U"fummo", U"foste", U"furono", U"fossi",
        U"fosse", U"fossimo", U"fossero", U"essendo", U"faccio", U"fai",
        U"facciamo", U"fanno", U"faccia", U"facciate", U"facciano", U"farò",
        U"farai", U"farà", U"faremo", U"farete", U"faranno", U"farei",
        U"faresti", U"farebbe", U"faremmo", U"fareste", U"farebbero", U"facevo",
        U"facevi", U"faceva", U"facevamo", U"facevate", U"facevano", U"feci",
        U"facesti", U"fece", U"facemmo", U"faceste", U"fecero", U"facessi",
        U"facesse", U"facessimo", U"facessero", U"facendo", U"sto", U"stai",
        U"sta", U"stiamo", U"stanno", U"stia", U"stiate", U"stiano", U"starò",
        U"starai", U"starà", U"staremo", U"starete", U"staranno", U"starei",
        U"staresti", U"starebbe", U"staremmo", U"stareste", U"starebbero",
        U"stavo", U"stavi", U"stava", U"stavamo", U"stavate", U"stavano",
        U"stetti", U"stesti", U"stette", U"stemmo", U"steste", U"stettero",
        U"stessi", U"stesse", U"stessimo", U"stessero", U"stando"
    };

    constexpr const omn::unicode::UTF32Character * nor[176] = // Norwegian
    {
        U"og", U"i", U"jeg", U"det", U"at", U"en", U"et", U"den", U"til", U"er",
        U"som", U"på", U"de", U"med", U"han", U"av", U"ikke", U"ikkje", U"der",
        U"så", U"var", U"meg", U"seg", U"men", U"ett", U"har", U"om", U"vi",
        U"min", U"mitt", U"ha", U"hadde", U"hun", U"nå", U"over", U"da", U"ved",
        U"fra", U"du", U"ut", U"sin", U"dem", U"oss", U"opp", U"man", U"kan",
        U"hans", U"hvor", U"eller", U"hva", U"skal", U"selv", U"sjøl", U"her",
        U"alle", U"vil", U"bli", U"ble", U"blei", U"blitt", U"kunne", U"inn",
        U"når", U"være", U"kom", U"noen", U"noe", U"ville", U"dere", U"som",
        U"deres", U"kun", U"ja", U"etter", U"ned", U"skulle", U"denne", U"for",
        U"deg", U"si", U"sine", U"sitt", U"mot", U"å", U"meget", U"hvorfor",
        U"dette", U"disse", U"uten", U"hvordan", U"ingen", U"din", U"ditt", U"blir",
        U"samme", U"hvilken", U"hvilke", U"sånn", U"inni", U"mellom", U"vår",
        U"hver", U"hvem", U"vors", U"hvis", U"både", U"bare", U"enn", U"fordi",
        U"før", U"mange", U"også", U"slik", U"vært", U"være", U"båe", U"begge",
        U"siden", U"dykk", U"dykkar", U"dei", U"deira", U"deires", U"deim", U"di",
        U"då", U"eg", U"ein", U"eit", U"eitt", U"elles", U"honom", U"hjå", U"ho",
        U"hoe", U"henne", U"hennar", U"hennes", U"hoss", U"hossen", U"ikkje", U"ingi",
        U"inkje", U"korleis", U"korso", U"kva", U"kvar", U"kvarhelst", U"kven",
        U"kvi", U"kvifor", U"me", U"medan", U"mi", U"mine", U"mykje", U"no",
        U"nokon", U"noka", U"nokor", U"noko", U"nokre", U"si", U"sia", U"sidan",
        U"so", U"somt", U"somme", U"um", U"upp", U"vere", U"vore", U"verte", U"vort",
        U"varte", U"vart"
    };

    constexpr const omn::unicode::UTF32Character * por[203] = // Portuguese
    {
        U"de", U"a", U"o", U"que", U"e", U"do", U"da", U"em", U"um", U"para",
        U"com", U"não", U"uma", U"os", U"no", U"se", U"na", U"por", U"mais",
        U"as", U"dos", U"como", U"mas", U"ao", U"ele", U"das", U"à", U"seu",
        U"sua", U"ou", U"quando", U"muito", U"nos", U"já", U"eu", U"também",
        U"só", U"pelo", U"pela", U"até", U"isso", U"ela", U"entre", U"depois",
        U"sem", U"mesmo", U"aos", U"seus", U"quem", U"nas", U"me", U"esse",
        U"eles", U"você", U"essa", U"num", U"nem", U"suas", U"meu", U"às",
        U"minha", U"numa", U"pelos", U"elas", U"qual", U"nós", U"lhe", U"deles",
        U"essas", U"esses", U"pelas", U"este", U"dele", U"tu", U"te", U"vocês",
        U"vos", U"lhes", U"meus", U"minhas", U"teu", U"tua", U"teus", U"tuas",
        U"nosso", U"nossa", U"nossos", U"nossas", U"dela", U"delas", U"esta",
        U"estes", U"estas", U"aquele", U"aquela", U"aqueles", U"aquelas", U"isto",
        U"aquilo", U"estou", U"está", U"estamos", U"estão", U"estive", U"esteve",
        U"estivemos", U"estiveram", U"estava", U"estávamos", U"estavam",
        U"estivera", U"estivéramos", U"esteja", U"estejamos", U"estejam",
        U"estivesse", U"estivéssemos", U"estivessem", U"estiver", U"estivermos",
        U"estiverem", U"hei", U"há", U"havemos", U"hão", U"houve", U"houvemos",
        U"houveram", U"houvera", U"houvéramos", U"haja", U"hajamos", U"hajam",
        U"houvesse", U"houvéssemos", U"houvessem", U"houver", U"houvermos",
        U"houverem", U"houverei", U"houverá", U"houveremos", U"houverão",
        U"houveria", U"houveríamos", U"houveriam", U"sou", U"somos", U"são",
        U"era", U"éramos", U"eram", U"fui", U"foi", U"fomos", U"foram", U"fora",
        U"fôramos", U"seja", U"sejamos", U"sejam", U"fosse", U"fôssemos",
        U"fossem", U"for", U"formos", U"forem", U"serei", U"será", U"seremos",
        U"serão", U"seria", U"seríamos", U"seriam", U"tenho", U"tem", U"temos",
        U"tém", U"tinha", U"tínhamos", U"tinham", U"tive", U"teve", U"tivemos",
        U"tiveram", U"tivera", U"tivéramos", U"tenha", U"tenhamos", U"tenham",
        U"tivesse", U"tivéssemos", U"tivessem", U"tiver", U"tivermos", U"tiverem",
        U"terei", U"terá", U"teremos", U"terão", U"teria", U"teríamos", U"teriam"
    };

    constexpr const omn::unicode::UTF32Character * rum[356] = // Romanian
    {
        U"a", U"abia", U"acea", U"aceasta", U"această", U"aceea", U"aceeasi",
        U"acei", U"aceia", U"acel", U"acela", U"acelasi", U"acele", U"acelea",
        U"acest", U"acesta", U"aceste", U"acestea", U"acestei", U"acestia",
        U"acestui", U"aceşti", U"aceştia", U"adica", U"ai", U"aia", U"aibă", U"aici",
        U"al", U"ala", U"ale", U"alea", U"alt", U"alta", U"altceva", U"altcineva",
        U"alte", U"altfel", U"alti", U"altii", U"altul", U"am", U"anume", U"apoi",
        U"ar", U"are", U"as", U"asa", U"asta", U"astea", U"astfel", U"asupra",
        U"atare", U"atat", U"atata", U"atatea", U"atatia", U"ati", U"atit", U"atita",
        U"atitea", U"atitia", U"atunci", U"au", U"avea", U"avem", U"aveţi", U"avut",
        U"aş", U"aţi", U"ba", U"ca", U"cam", U"cand", U"care", U"careia", U"carora",
        U"caruia", U"cat", U"catre", U"ce", U"cea", U"ceea", U"cei", U"ceilalti",
        U"cel", U"cele", U"celor", U"ceva", U"chiar", U"ci", U"cind", U"cine",
        U"cineva", U"cit", U"cita", U"cite", U"citeva", U"citi", U"citiva", U"cu",
        U"cui", U"cum", U"cumva", U"cât", U"câte", U"câtva", U"câţi", U"cînd",
        U"cît", U"cîte", U"cîtva", U"cîţi", U"că", U"căci", U"cărei", U"căror",
        U"cărui", U"către", U"da", U"daca", U"dacă", U"dar", U"dat", U"dată", U"dau",
        U"de", U"deasupra", U"deci", U"decit", U"deja", U"desi", U"despre", U"deşi",
        U"din", U"dintr", U"dintr-", U"dintre", U"doar", U"doi", U"doilea", U"două",
        U"drept", U"dupa", U"după", U"dă", U"e", U"ea", U"ei", U"el", U"ele",
        U"era", U"eram", U"este", U"eu", U"eşti", U"face", U"fara", U"fata", U"fel",
        U"fi", U"fie", U"fiecare", U"fii", U"fim", U"fiu", U"fiţi", U"foarte",
        U"fost", U"fără", U"i", U"ia", U"iar", U"ii", U"il", U"imi", U"in",
        U"inainte", U"inapoi", U"inca", U"incit", U"insa", U"intr", U"intre", U"isi",
        U"iti", U"la", U"le", U"li", U"lor", U"lui", U"lângă", U"lîngă", U"m",
        U"ma", U"mai", U"mea", U"mei", U"mele", U"mereu", U"meu", U"mi", U"mie",
        U"mine", U"mod", U"mult", U"multa", U"multe", U"multi", U"multă", U"mulţi",
        U"mâine", U"mîine", U"mă", U"ne", U"ni", U"nici", U"nimeni", U"nimic",
        U"niste", U"nişte", U"noastre", U"noastră", U"noi", U"nostri", U"nostru",
        U"nou", U"noua", U"nouă", U"noştri", U"nu", U"numai", U"o", U"or", U"ori",
        U"oricare", U"orice", U"oricine", U"oricum", U"oricând", U"oricât",
        U"oricînd", U"oricît", U"oriunde", U"pai", U"parca", U"patra", U"patru",
        U"pe", U"pentru", U"peste", U"pic", U"pina", U"poate", U"pot", U"prea",
        U"prima", U"primul", U"prin", U"printr-", U"putini", U"puţin", U"puţina",
        U"puţină", U"până", U"pînă", U"sa", U"sa-mi", U"sa-ti", U"sai", U"sale",
        U"sau", U"se", U"si", U"sint", U"sintem", U"spate", U"spre", U"sub",
        U"sunt", U"suntem", U"sunteţi", U"sus", U"să", U"săi", U"său", U"t",
        U"ta", U"tale", U"te", U"ti", U"tine", U"toata", U"toate", U"toată",
        U"tocmai", U"tot", U"toti", U"totul", U"totusi", U"totuşi", U"toţi",
        U"trei", U"treia", U"treilea", U"tu", U"tuturor", U"tăi", U"tău", U"u",
        U"ul", U"ului", U"un", U"una", U"unde", U"undeva", U"unei", U"uneia",
        U"unele", U"uneori", U"unii", U"unor", U"unora", U"unu", U"unui", U"unuia",
        U"unul", U"v", U"va", U"vi", U"voastre", U"voastră", U"voi", U"vom", U"vor",
        U"vostru", U"vouă", U"voştri", U"vreo", U"vreun", U"vă", U"zi", U"zice",
        U"îi", U"îl", U"îmi", U"în", U"îţi", U"ăla", U"ălea", U"ăsta", U"ăstea",
        U"ăştia", U"şi", U"ţi", U"ţie"
    };

    constexpr const omn::unicode::UTF32Character * rus[150] = // Russian
    {
        U"а", U"без", U"более", U"больше", U"будет", U"будто", U"бы", U"был",
        U"была", U"были", U"было", U"быть", U"в", U"вам", U"вас", U"вдруг",
        U"ведь", U"во", U"вот", U"впрочем", U"все", U"всегда", U"всего", U"всех",
        U"всю", U"вы", U"где", U"да", U"даже", U"два", U"для", U"до", U"другой",
        U"его", U"ее", U"ей", U"ему", U"если", U"есть", U"еще", U"ж", U"же",
        U"за", U"зачем", U"здесь", U"и", U"из", U"или", U"им", U"иногда", U"их",
        U"к", U"как", U"какая", U"какой", U"когда", U"конечно", U"кто", U"куда",
        U"ли", U"лучше", U"между", U"мне", U"много", U"может", U"можно", U"мой",
        U"моя", U"мы", U"на", U"над", U"надо", U"наконец", U"нас", U"не", U"него",
        U"нее", U"ней", U"нельзя", U"нет", U"ни", U"нибудь", U"никогда", U"ним",
        U"них", U"ничего", U"но", U"ну", U"о", U"об", U"один", U"он", U"она",
        U"они", U"опять", U"от", U"перед", U"по", U"под", U"после", U"потом",
        U"потому", U"почти", U"при", U"про", U"раз", U"разве", U"с", U"сам",
        U"свою", U"себе", U"себя", U"сейчас", U"со", U"совсем", U"так", U"такой",
        U"там", U"тебя", U"тем", U"теперь", U"то", U"тогда", U"того", U"тоже",
        U"только", U"том", U"тот", U"три", U"тут", U"ты", U"у", U"уж", U"уже",
        U"хорошо", U"хоть", U"чего", U"чем", U"через", U"что", U"чтоб", U"чтобы",
        U"чуть", U"эти", U"этого", U"этой", U"этом", U"этот", U"эту", U"я"
    };

    constexpr const omn::unicode::UTF32Character * spa[315] = // Spanish
    {
        U"¡", U"¿", U"de", U"la", U"que", U"el", U"en", U"y", U"a", U"los", U"del",
        U"se", U"las", U"por", U"un", U"para", U"con", U"no", U"una", U"su", U"al",
        U"lo", U"como", U"más", U"pero", U"sus", U"le", U"ya", U"o", U"este",
        U"sí", U"porque", U"esta", U"entre", U"cuando", U"muy", U"sin", U"sobre",
        U"también", U"me", U"hasta", U"hay", U"donde", U"quien", U"desde", U"todo",
        U"nos", U"durante", U"todos", U"uno", U"les", U"ni", U"contra", U"otros",
        U"ese", U"eso", U"ante", U"ellos", U"e", U"esto", U"mí", U"antes",
        U"algunos", U"qué", U"unos", U"yo", U"otro", U"otras", U"otra", U"él",
        U"tanto", U"esa", U"estos", U"mucho", U"quienes", U"nada", U"muchos",
        U"cual", U"poco", U"ella", U"estar", U"estas", U"algunas", U"algo",
        U"nosotros", U"mi", U"mis", U"tú", U"te", U"ti", U"tu", U"tus", U"ellas",
        U"nosotras", U"vosostros", U"vosostras", U"os", U"mío", U"mía", U"míos",
        U"mías", U"tuyo", U"tuya", U"tuyos", U"tuyas", U"suyo", U"suya", U"suyos",
        U"suyas", U"nuestro", U"nuestra", U"nuestros", U"nuestras", U"vuestro",
        U"vuestra", U"vuestros", U"vuestras", U"esos", U"esas", U"estoy", U"estás",
        U"está", U"estamos", U"estáis", U"están", U"esté", U"estés", U"estemos",
        U"estéis", U"estén", U"estaré", U"estarás", U"estará", U"estaremos",
        U"estaréis", U"estarán", U"estaría", U"estarías", U"estaríamos",
        U"estaríais", U"estarían", U"estaba", U"estabas", U"estábamos", U"estabais",
        U"estaban", U"estuve", U"estuviste", U"estuvo", U"estuvimos", U"estuvisteis",
        U"estuvieron", U"estuviera", U"estuvieras", U"estuviéramos", U"estuvierais",
        U"estuvieran", U"estuviese", U"estuvieses", U"estuviésemos", U"estuvieseis",
        U"estuviesen", U"estando", U"estado", U"estada", U"estados", U"estadas",
        U"estad", U"he", U"has", U"ha", U"hemos", U"habéis", U"han", U"haya",
        U"hayas", U"hayamos", U"hayáis", U"hayan", U"habré", U"habrás", U"habrá",
        U"habremos", U"habréis", U"habrán", U"habría", U"habrías", U"habríamos",
        U"habríais", U"habrían", U"había", U"habías", U"habíamos", U"habíais",
        U"habían", U"hube", U"hubiste", U"hubo", U"hubimos", U"hubisteis",
        U"hubieron", U"hubiera", U"hubieras", U"hubiéramos", U"hubierais",
        U"hubieran", U"hubiese", U"hubieses", U"hubiésemos", U"hubieseis",
        U"hubiesen", U"habiendo", U"habido", U"habida", U"habidos", U"habidas",
        U"soy", U"eres", U"es", U"somos", U"sois", U"son", U"sea", U"seas",
        U"seamos", U"seáis", U"sean", U"seré", U"serás", U"será", U"seremos",
        U"seréis", U"serán", U"sería", U"serías", U"seríamos", U"seríais",
        U"serían", U"era", U"eras", U"éramos", U"erais", U"eran", U"fui",
        U"fuiste", U"fue", U"fuimos", U"fuisteis", U"fueron", U"fuera", U"fueras",
        U"fuéramos", U"fuerais", U"fueran", U"fuese", U"fueses", U"fuésemos",
        U"fueseis", U"fuesen", U"sintiendo", U"sentido", U"sentida", U"sentidos",
        U"sentidas", U"siente", U"sentid", U"tengo", U"tienes", U"tiene",
        U"tenemos", U"tenéis", U"tienen", U"tenga", U"tengas", U"tengamos",
        U"tengáis", U"tengan", U"tendré", U"tendrás", U"tendrá", U"tendremos",
        U"tendréis", U"tendrán", U"tendría", U"tendrías", U"tendríamos",
        U"tendríais", U"tendrían", U"tenía", U"tenías", U"teníamos", U"teníais",
        U"tenían", U"tuve", U"tuviste", U"tuvo", U"tuvimos", U"tuvisteis",
        U"tuvieron", U"tuviera", U"tuvieras", U"tuviéramos", U"tuvierais",
        U"tuvieran", U"tuviese", U"tuvieses", U"tuviésemos", U"tuvieseis",
        U"tuviesen", U"teniendo", U"tenido", U"tenida", U"tenidos", U"tenidas", U"tened"
    };

    constexpr const omn::unicode::UTF32Character * swe[114] = // Swedish
    {
        U"och", U"det", U"att", U"i", U"en", U"jag", U"hon", U"som", U"han", U"på",
        U"den", U"med", U"var", U"sig", U"för", U"så", U"till", U"är", U"men",
        U"ett", U"om", U"hade", U"de", U"av", U"icke", U"mig", U"du", U"henne",
        U"då", U"sin", U"nu", U"har", U"inte", U"hans", U"honom", U"skulle",
        U"hennes", U"där", U"min", U"man", U"ej", U"vid", U"kunde", U"något",
        U"från", U"ut", U"när", U"efter", U"upp", U"vi", U"dem", U"vara", U"vad",
        U"över", U"än", U"dig", U"kan", U"sina", U"här", U"ha", U"mot", U"alla",
        U"under", U"någon", U"eller", U"allt", U"mycket", U"sedan", U"ju", U"denna",
        U"själv", U"detta", U"åt", U"utan", U"varit", U"hur", U"ingen", U"mitt",
        U"ni", U"bli", U"blev", U"oss", U"din", U"dessa", U"några", U"deras",
        U"blir", U"mina", U"samma", U"vilken", U"er", U"sådan", U"vår", U"blivit",
        U"dess", U"inom", U"mellan", U"sådant", U"varför", U"varje", U"vilka",
        U"ditt", U"vem", U"vilket", U"sitta", U"sådana", U"vart", U"dina", U"vars",
        U"vårt", U"våra", U"ert", U"era", U"vilkas"
    };

    constexpr const omn::unicode::UTF32Character * tur[53] = // Turkish
    {
        U"acaba", U"ama", U"aslında", U"az", U"bazı", U"belki", U"biri",
        U"birkaç",U"birşey", U"biz", U"bu", U"çok", U"çünkü", U"da", U"daha",
        U"de", U"defa", U"diye", U"eğer", U"en", U"gibi", U"hem", U"hep",
        U"hepsi", U"her", U"hiç", U"için", U"ile", U"ise", U"kez", U"ki",
        U"kim", U"mı", U"mu", U"mü", U"nasıl", U"ne", U"neden", U"nerde",
        U"nerede", U"nereye", U"niçin", U"niye", U"o", U"sanki", U"şey",
        U"siz", U"şu", U"tüm", U"ve", U"veya", U"ya", U"yani"
    };

    constexpr const omn::unicode::UTF32Character * vie[201] = // Vietnamese*
    {
        U"và", U"là", U"của", U"một", U"được", U"trong", U"các", U"có", U"năm",
        U"với", U"tại", U"người", U"cho", U"đã", U"quan", U"này", U"vào", U"không",
        U"thành", U"đầu", U"từ", U"những", U"số", U"học", U"liên", U"tháng",
        U"thể", U"tới", U"khi", U"sự", U"ra", U"đến", U"họ", U"như", U"gia",
        U"trên", U"ngày", U"đó", U"về", U"công", U"chính", U"để", U"động", U"nước",
        U"loài", U"kết", U"c", U"vật", U"thích", U"thực", U"nhất", U"quân", U"bị",
        U"nhiều", U"thế", U"hiện", U"sau", U"phát", U"cũng", U"khác", U"liệu", U"ở",
        U"nhà", U"làm", U"dân", U"ngoài", U"theo", U"thời", U"lại", U"khảo", U"tiên",
        U"do", U"nhân", U"thuộc", U"chỉ", U"sinh", U"hành", U"định", U"sử", U"hai",
        U"bộ", U"dụng", U"quốc", U"hơn", U"ông", U"việc", U"hình", U"chiến", U"giới",
        U"tế", U"lớn", U"khoa", U"ca", U"độ", U"con", U"thứ", U"lượng", U"tả",
        U"còn", U"chủ", U"cách", U"xuất", U"ả", U"hợp", U"thống", U"xã", U"hội",
        U"thường", U"tranh", U"lý", U"sản", U"bằng", U"cơ", U"cao", U"loại", U"hoặc",
        U"chức", U"tự", U"đồng", U"hay", U"ừ", U"cùng", U"th", U"phần", U"lập",
        U"hóa", U"tiếng", U"gồm", U"viên", U"trường", U"rằng", U"đại", U"bản", U"mà",
        U"hệ", U"cả", U"tính", U"tập", U"trình", U"thị", U"tiện", U"cuộc", U"vị",
        U"tạo", U"thông", U"nhận", U"nó", U"đối", U"thức", U"mô", U"phân", U"phải",
        U"nhưng", U"qua", U"lực", U"trị", U"kinh", U"bởi", U"gọi", U"tên", U"triển",
        U"trước", U"nh", U"điều", U"bao", U"trở", U"hàng", U"cc", U"sẽ", U"quyền",
        U"địa", U"ạ", U"tỉnh", U"đội", U"trung", U"cấp", U"năng", U"giải", U"tiếp",
        U"nhau", U"vi", U"nghiệp", U"giáo", U"điểm", U"nhiên", U"tác", U"vùng",
        U"khoảng", U"lên", U"sống", U"phía", U"mt", U"lần", U"tin", U"toàn", U"vụ",
        U"nghĩa", U"thì", U"tăng", U"khu", U"ý"
    };

    constexpr const omn::unicode::UTF32Character * const * all[omn::ISO6392LanguageCode::zza + 1] =
    {
        /*zxx*/ 0,
        /*aar*/ 0,   /*abk*/ 0,   /*afr*/ 0,   /*aka*/ 0,   /*alb*/ 0,   /*amh*/ 0,
        /*ara*/ ara, /*arg*/ 0,   /*arm*/ 0,   /*asm*/ 0,   /*ava*/ 0,   /*ave*/ 0,
        /*aym*/ 0,   /*aze*/ aze, /*bak*/ 0,   /*bam*/ 0,   /*baq*/ 0,   /*bel*/ 0,
        /*ben*/ 0,   /*bih*/ 0,   /*bis*/ 0,   /*bos*/ 0,   /*bre*/ 0,   /*bul*/ 0,
        /*bur*/ 0,   /*cat*/ 0,   /*cha*/ 0,   /*che*/ 0,   /*chi*/ 0,   /*chu*/ 0,
        /*chv*/ 0,   /*cor*/ 0,   /*cos*/ 0,   /*cre*/ 0,   /*cze*/ 0,   /*dan*/ dan,
        /*div*/ 0,   /*dut*/ dut, /*dzo*/ 0,   /*eng*/ eng, /*epo*/ 0,   /*est*/ 0,
        /*ewe*/ 0,   /*fao*/ 0,   /*fij*/ 0,   /*fin*/ fin, /*fre*/ fre, /*fry*/ 0,
        /*ful*/ 0,   /*geo*/ 0,   /*ger*/ ger, /*gla*/ 0,   /*gle*/ gle, /*glg*/ 0,
        /*glv*/ 0,   /*gre*/ gre, /*grn*/ 0,   /*guj*/ 0,   /*hat*/ 0,   /*hau*/ 0,
        /*heb*/ 0,   /*her*/ 0,   /*hin*/ 0,   /*hmo*/ 0,   /*hrv*/ 0,   /*hun*/ hun,
        /*ibo*/ 0,   /*ice*/ 0,   /*ido*/ 0,   /*iii*/ 0,   /*iku*/ 0,   /*ile*/ 0,
        /*ina*/ 0,   /*ind*/ 0,   /*ipk*/ 0,   /*ita*/ ita, /*jav*/ 0,   /*jpn*/ 0,
        /*kal*/ 0,   /*kan*/ 0,   /*kas*/ 0,   /*kau*/ 0,   /*kaz*/ 0,   /*khm*/ 0,
        /*kik*/ 0,   /*kin*/ 0,   /*kir*/ 0,   /*kom*/ 0,   /*kon*/ 0,   /*kor*/ 0,
        /*kua*/ 0,   /*kur*/ 0,   /*lao*/ 0,   /*lat*/ 0,   /*lav*/ 0,   /*lim*/ 0,
        /*lin*/ 0,   /*lit*/ 0,   /*ltz*/ 0,   /*lub*/ 0,   /*lug*/ 0,   /*mac*/ 0,
        /*mah*/ 0,   /*mal*/ 0,   /*mao*/ 0,   /*mar*/ 0,   /*may*/ 0,   /*mlg*/ 0,
        /*mlt*/ 0,   /*mon*/ 0,   /*nau*/ 0,   /*nav*/ 0,   /*nbl*/ 0,   /*nde*/ 0,
        /*ndo*/ 0,   /*nep*/ 0,   /*nor*/ nor, /*nya*/ 0,   /*oci*/ 0,   /*oji*/ 0,
        /*ori*/ 0,   /*orm*/ 0,   /*oss*/ 0,   /*pan*/ 0,   /*per*/ 0,   /*pli*/ 0,
        /*pol*/ 0,   /*por*/ por, /*pus*/ 0,   /*que*/ 0,   /*roh*/ 0,   /*rum*/ rum,
        /*run*/ 0,   /*rus*/ rus, /*sag*/ 0,   /*san*/ 0,   /*sin*/ 0,   /*slo*/ 0,
        /*slv*/ 0,   /*sme*/ 0,   /*smo*/ 0,   /*sna*/ 0,   /*snd*/ 0,   /*som*/ 0,
        /*sot*/ 0,   /*spa*/ spa, /*srd*/ 0,   /*srp*/ 0,   /*ssw*/ 0,   /*sun*/ 0,
        /*swa*/ 0,   /*swe*/ swe, /*tah*/ 0,   /*tam*/ 0,   /*tat*/ 0,   /*tel*/ 0,
        /*tgk*/ 0,   /*tgl*/ 0,   /*tha*/ 0,   /*tib*/ 0,   /*tir*/ 0,   /*ton*/ 0,
        /*tsn*/ 0,   /*tso*/ 0,   /*tuk*/ 0,   /*tur*/ tur, /*twi*/ 0,   /*uig*/ 0,
        /*ukr*/ 0,   /*urd*/ 0,   /*uzb*/ 0,   /*ven*/ 0,   /*vie*/ vie, /*vol*/ 0,
        /*wel*/ 0,   /*wln*/ 0,   /*wol*/ 0,   /*xho*/ 0,   /*yid*/ 0,   /*yor*/ 0,
        /*zha*/ 0,   /*zul*/ 0,   /*ace*/ 0,   /*ach*/ 0,   /*ada*/ 0,   /*ady*/ 0,
        /*afh*/ 0,   /*ain*/ 0,   /*akk*/ 0,   /*ale*/ 0,   /*alg*/ 0,   /*alt*/ 0,
        /*ang*/ 0,   /*anp*/ 0,   /*apa*/ 0,   /*arc*/ 0,   /*arn*/ 0,   /*arp*/ 0,
        /*arw*/ 0,   /*ast*/ 0,   /*ath*/ 0,   /*aus*/ 0,   /*awa*/ 0,   /*bad*/ 0,
        /*bai*/ 0,   /*bal*/ 0,   /*ban*/ 0,   /*bas*/ 0,   /*bej*/ 0,   /*bem*/ 0,
        /*ber*/ 0,   /*bho*/ 0,   /*bik*/ 0,   /*bin*/ 0,   /*bla*/ 0,   /*bra*/ 0,
        /*btk*/ 0,   /*bua*/ 0,   /*bug*/ 0,   /*byn*/ 0,   /*cad*/ 0,   /*cai*/ 0,
        /*car*/ 0,   /*ceb*/ 0,   /*chb*/ 0,   /*chg*/ 0,   /*chk*/ 0,   /*chm*/ 0,
        /*chn*/ 0,   /*cho*/ 0,   /*chp*/ 0,   /*chr*/ 0,   /*chy*/ 0,   /*cmc*/ 0,
        /*cnr*/ 0,   /*cop*/ 0,   /*cpe*/ 0,   /*cpf*/ 0,   /*cpp*/ 0,   /*crh*/ 0,
        /*csb*/ 0,   /*dak*/ 0,   /*dar*/ 0,   /*day*/ 0,   /*del*/ 0,   /*den*/ 0,
        /*dgr*/ 0,   /*din*/ 0,   /*doi*/ 0,   /*dsb*/ 0,   /*dua*/ 0,   /*dum*/ 0,
        /*dyu*/ 0,   /*efi*/ 0,   /*egy*/ 0,   /*eka*/ 0,   /*elx*/ 0,   /*enm*/ 0,
        /*ewo*/ 0,   /*fan*/ 0,   /*fat*/ 0,   /*fon*/ 0,   /*frm*/ 0,   /*fro*/ 0,
        /*frr*/ 0,   /*frs*/ 0,   /*fur*/ 0,   /*gaa*/ 0,   /*gay*/ 0,   /*gba*/ 0,
        /*gez*/ 0,   /*gil*/ 0,   /*gmh*/ 0,   /*goh*/ 0,   /*gon*/ 0,   /*gor*/ 0,
        /*got*/ 0,   /*grb*/ 0,   /*grc*/ 0,   /*gsw*/ 0,   /*gwi*/ 0,   /*hai*/ 0,
        /*haw*/ 0,   /*hil*/ 0,   /*him*/ 0,   /*hit*/ 0,   /*hmn*/ 0,   /*hsb*/ 0,
        /*hup*/ 0,   /*iba*/ 0,   /*ijo*/ 0,   /*ilo*/ 0,   /*inh*/ 0,   /*iro*/ 0,
        /*jbo*/ 0,   /*jpr*/ 0,   /*jrb*/ 0,   /*kaa*/ 0,   /*kab*/ 0,   /*kac*/ 0,
        /*kam*/ 0,   /*kar*/ 0,   /*kaw*/ 0,   /*kbd*/ 0,   /*kha*/ 0,   /*khi*/ 0,
        /*kho*/ 0,   /*kmb*/ 0,   /*kok*/ 0,   /*kos*/ 0,   /*kpe*/ 0,   /*krc*/ 0,
        /*krl*/ 0,   /*kro*/ 0,   /*kru*/ 0,   /*kum*/ 0,   /*kut*/ 0,   /*lad*/ 0,
        /*lah*/ 0,   /*lam*/ 0,   /*lez*/ 0,   /*lol*/ 0,   /*loz*/ 0,   /*lua*/ 0,
        /*lui*/ 0,   /*lun*/ 0,   /*luo*/ 0,   /*lus*/ 0,   /*mad*/ 0,   /*mag*/ 0,
        /*mai*/ 0,   /*mak*/ 0,   /*man*/ 0,   /*mas*/ 0,   /*mdf*/ 0,   /*mdr*/ 0,
        /*men*/ 0,   /*mga*/ 0,   /*mic*/ 0,   /*min*/ 0,   /*mis*/ 0,   /*mkh*/ 0,
        /*mnc*/ 0,   /*mni*/ 0,   /*mno*/ 0,   /*moh*/ 0,   /*mos*/ 0,   /*mul*/ 0,
        /*mun*/ 0,   /*mus*/ 0,   /*mwl*/ 0,   /*mwr*/ 0,   /*myn*/ 0,   /*myv*/ 0,
        /*nah*/ 0,   /*nai*/ 0,   /*nap*/ 0,   /*nds*/ 0,   /*new*/ 0,   /*nia*/ 0,
        /*niu*/ 0,   /*nog*/ 0,   /*non*/ 0,   /*nqo*/ 0,   /*nso*/ 0,   /*nub*/ 0,
        /*nwc*/ 0,   /*nym*/ 0,   /*nyn*/ 0,   /*nyo*/ 0,   /*nzi*/ 0,   /*osa*/ 0,
        /*ota*/ 0,   /*oto*/ 0,   /*paa*/ 0,   /*pag*/ 0,   /*pal*/ 0,   /*pam*/ 0,
        /*pap*/ 0,   /*pau*/ 0,   /*peo*/ 0,   /*phi*/ 0,   /*phn*/ 0,   /*pon*/ 0,
        /*pra*/ 0,   /*pro*/ 0,   /*raj*/ 0,   /*rap*/ 0,   /*rar*/ 0,   /*rom*/ 0,
        /*rup*/ 0,   /*sad*/ 0,   /*sah*/ 0,   /*sai*/ 0,   /*sal*/ 0,   /*sam*/ 0,
        /*sas*/ 0,   /*sat*/ 0,   /*scn*/ 0,   /*sco*/ 0,   /*sel*/ 0,   /*sga*/ 0,
        /*shn*/ 0,   /*sid*/ 0,   /*sio*/ 0,   /*sma*/ 0,   /*smj*/ 0,   /*smn*/ 0,
        /*sms*/ 0,   /*snk*/ 0,   /*sog*/ 0,   /*son*/ 0,   /*srn*/ 0,   /*srr*/ 0,
        /*suk*/ 0,   /*sus*/ 0,   /*sux*/ 0,   /*syc*/ 0,   /*syr*/ 0,   /*tai*/ 0,
        /*tem*/ 0,   /*ter*/ 0,   /*tet*/ 0,   /*tig*/ 0,   /*tiv*/ 0,   /*tkl*/ 0,
        /*tlh*/ 0,   /*tli*/ 0,   /*tmh*/ 0,   /*tog*/ 0,   /*tpi*/ 0,   /*tsi*/ 0,
        /*tum*/ 0,   /*tup*/ 0,   /*tut*/ 0,   /*tvl*/ 0,   /*tyv*/ 0,   /*udm*/ 0,
        /*uga*/ 0,   /*umb*/ 0,   /*vai*/ 0,   /*vot*/ 0,   /*wak*/ 0,   /*wal*/ 0,
        /*war*/ 0,   /*was*/ 0,   /*wen*/ 0,   /*xal*/ 0,   /*yao*/ 0,   /*yap*/ 0,
        /*ypk*/ 0,   /*zap*/ 0,   /*zbl*/ 0,   /*zen*/ 0,   /*zgh*/ 0,   /*znd*/ 0,
        /*zun*/ 0,   /*zza*/ 0
    };
}

namespace omn
{
    namespace stopwords
    {
        class index
        {
            public:

            using iterator = unorderedMap<unicode::UTF32String, set<ISO6392LanguageCode>>::const_iterator;

            protected:

            unorderedMap<unicode::UTF32String, set<ISO6392LanguageCode>> Entries;

            inline void insertAll( const unicode::UTF32Character * const * UTF32Words,
                                   const size_t count,
                                   ISO6392LanguageCode language )
            {
                for (size_t i = 0; i < count; i++)
                    this->Entries[unicode::UTF32String(UTF32Words[i])].insert(language);
            }

            void insertAllByLanguage( ISO6392LanguageCode language );

            public:

            index();

            index( ISO6392LanguageCode language );

            index( const unicode::UTF32Character * const * stopwordsList,
                   size_t count,
                   ISO6392LanguageCode language = ISO6392LanguageCode::und );

            inline void clear()
            {
                this->Entries.clear();
            }

            inline bool isEmpty() const
            {
                return this->Entries.empty();
            }

            inline size_t size() const
            {
                return this->Entries.size();
            }

            inline uint16_t stopwordsCount() const
            {
                return this->Entries.size();
            }

            inline iterator begin() const
            {
                return this->Entries.begin();
            }

            inline iterator end() const
            {
                return this->Entries.end();
            }

            inline ISO6392LanguageCode add( unicode::UTF32String & UTF32Word,
                                            ISO6392LanguageCode language = ISO6392LanguageCode::und )
            {
                if (language == ISO6392LanguageCode::mis) language = ISO6392LanguageCode::und;
                if (language == ISO6392LanguageCode::und) this->Entries[UTF32Word];
                else this->Entries[UTF32Word].insert(language);
                return languageOf(UTF32Word);
            }

            inline void remove( unicode::UTF32String & UTF32Word,
                                ISO6392LanguageCode language = ISO6392LanguageCode::mul )
            {
                if (!this->Entries.count(UTF32Word)) return;
                if (language == ISO6392LanguageCode::mis) return;
                if (language == ISO6392LanguageCode::und) return;
                if (language == ISO6392LanguageCode::mul) this->Entries.erase(UTF32Word);
                else this->Entries[UTF32Word].erase(language);
            }

            inline void load( ISO6392LanguageCode language )
            {
                this->insertAllByLanguage(language);
            }

            inline ISO6392LanguageCode languageOf( unicode::UTF32String UTF32Word ) const
            {
                if (!this->Entries.count(UTF32Word)) return ISO6392LanguageCode::und;
                switch (this->Entries.at(UTF32Word).size())
                {
                    case 1: return (*(this->Entries.at(UTF32Word).begin()));
                    case 0: return ISO6392LanguageCode::und;
                    default: return ISO6392LanguageCode::mul;
                }
            }

            inline set<ISO6392LanguageCode> languagesOf( unicode::UTF32String UTF32Word ) const
            {
                if (!this->Entries.count(UTF32Word)) return set<ISO6392LanguageCode>{};
                return this->Entries.at(UTF32Word);
            }

            inline size_t languageCountOf( unicode::UTF32String UTF32Word ) const
            {
                if (!this->Entries.count(UTF32Word)) return 0;
                return this->Entries.at(UTF32Word).size();
            }

            inline bool contains( unicode::UTF32String UTF32Word ) const
            {
                return (this->Entries.count(UTF32Word));
            }

            inline bool isStopword( unicode::UTF32String UTF32Word ) const
            {
                return (this->Entries.count(UTF32Word));
            }

            inline bool isStopword( unicode::UTF32String UTF32Word, ISO6392LanguageCode language ) const
            {
                return (this->languageOf(UTF32Word) == language);
            }
        };

        tokenization::tokenizedString listByLanguage( const ISO6392LanguageCode language );
    }
}

#endif // _OMN_STOPWORDS_INCLUDED
