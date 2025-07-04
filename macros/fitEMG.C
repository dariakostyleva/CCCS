#include <TCanvas.h>
#include <TFile.h>
#include <TH1F.h>
#include <TF1.h>
#include <TGraph.h>
/*
Double_t expModGauss(Double_t *x, Double_t *par) {
    Double_t mu = par[0];      // Mean of the Gaussian
    Double_t sigma = par[1];   // Standard deviation of the Gaussian
    Double_t lambda = par[2];  // Decay rate of the exponential

    //Double_t z = (x[0] - mu) / sigma;
    Double_t expPart = lambda / 2 * TMath::Exp(lambda / 2 * (2 * mu + lambda * sigma * sigma - 2 * x[0]));
    Double_t erfcPart = TMath::Erfc((mu + lambda * sigma * sigma - x[0]) / (TMath::Sqrt(2) * sigma));
    
    return expPart * erfcPart;
}
*/
void fitEMG() {
    // Create a sample histogram
    TH1F *h_z2_cut__1 = new TH1F("h_z2_cut__1","Z2 from MUSIC42, after target, with condition on Z1 and TPC",500,4,10);
   h_z2_cut__1->SetBinContent(0,367);
   h_z2_cut__1->SetBinContent(1,5);
   h_z2_cut__1->SetBinContent(5,2);
   h_z2_cut__1->SetBinContent(6,2);
   h_z2_cut__1->SetBinContent(7,3);
   h_z2_cut__1->SetBinContent(8,1);
   h_z2_cut__1->SetBinContent(9,3);
   h_z2_cut__1->SetBinContent(11,1);
   h_z2_cut__1->SetBinContent(13,1);
   h_z2_cut__1->SetBinContent(14,1);
   h_z2_cut__1->SetBinContent(24,1);
   h_z2_cut__1->SetBinContent(26,3);
   h_z2_cut__1->SetBinContent(27,1);
   h_z2_cut__1->SetBinContent(28,2);
   h_z2_cut__1->SetBinContent(29,1);
   h_z2_cut__1->SetBinContent(30,1);
   h_z2_cut__1->SetBinContent(31,5);
   h_z2_cut__1->SetBinContent(33,1);
   h_z2_cut__1->SetBinContent(34,2);
   h_z2_cut__1->SetBinContent(35,2);
   h_z2_cut__1->SetBinContent(36,1);
   h_z2_cut__1->SetBinContent(37,1);
   h_z2_cut__1->SetBinContent(38,1);
   h_z2_cut__1->SetBinContent(42,2);
   h_z2_cut__1->SetBinContent(43,2);
   h_z2_cut__1->SetBinContent(45,1);
   h_z2_cut__1->SetBinContent(46,2);
   h_z2_cut__1->SetBinContent(50,2);
   h_z2_cut__1->SetBinContent(52,1);
   h_z2_cut__1->SetBinContent(54,2);
   h_z2_cut__1->SetBinContent(63,1);
   h_z2_cut__1->SetBinContent(64,1);
   h_z2_cut__1->SetBinContent(66,1);
   h_z2_cut__1->SetBinContent(68,2);
   h_z2_cut__1->SetBinContent(72,1);
   h_z2_cut__1->SetBinContent(80,1);
   h_z2_cut__1->SetBinContent(83,1);
   h_z2_cut__1->SetBinContent(89,1);
   h_z2_cut__1->SetBinContent(90,1);
   h_z2_cut__1->SetBinContent(91,2);
   h_z2_cut__1->SetBinContent(93,2);
   h_z2_cut__1->SetBinContent(94,1);
   h_z2_cut__1->SetBinContent(96,1);
   h_z2_cut__1->SetBinContent(97,2);
   h_z2_cut__1->SetBinContent(98,2);
   h_z2_cut__1->SetBinContent(99,1);
   h_z2_cut__1->SetBinContent(100,3);
   h_z2_cut__1->SetBinContent(101,3);
   h_z2_cut__1->SetBinContent(102,1);
   h_z2_cut__1->SetBinContent(103,1);
   h_z2_cut__1->SetBinContent(104,5);
   h_z2_cut__1->SetBinContent(105,2);
   h_z2_cut__1->SetBinContent(106,2);
   h_z2_cut__1->SetBinContent(107,4);
   h_z2_cut__1->SetBinContent(111,2);
   h_z2_cut__1->SetBinContent(113,1);
   h_z2_cut__1->SetBinContent(115,1);
   h_z2_cut__1->SetBinContent(119,1);
   h_z2_cut__1->SetBinContent(120,1);
   h_z2_cut__1->SetBinContent(122,1);
   h_z2_cut__1->SetBinContent(126,1);
   h_z2_cut__1->SetBinContent(128,1);
   h_z2_cut__1->SetBinContent(129,2);
   h_z2_cut__1->SetBinContent(133,1);
   h_z2_cut__1->SetBinContent(134,2);
   h_z2_cut__1->SetBinContent(135,2);
   h_z2_cut__1->SetBinContent(138,1);
   h_z2_cut__1->SetBinContent(139,1);
   h_z2_cut__1->SetBinContent(140,2);
   h_z2_cut__1->SetBinContent(149,1);
   h_z2_cut__1->SetBinContent(152,1);
   h_z2_cut__1->SetBinContent(154,1);
   h_z2_cut__1->SetBinContent(159,2);
   h_z2_cut__1->SetBinContent(160,1);
   h_z2_cut__1->SetBinContent(162,1);
   h_z2_cut__1->SetBinContent(163,1);
   h_z2_cut__1->SetBinContent(164,1);
   h_z2_cut__1->SetBinContent(165,1);
   h_z2_cut__1->SetBinContent(166,1);
   h_z2_cut__1->SetBinContent(167,4);
   h_z2_cut__1->SetBinContent(168,2);
   h_z2_cut__1->SetBinContent(169,1);
   h_z2_cut__1->SetBinContent(170,3);
   h_z2_cut__1->SetBinContent(171,1);
   h_z2_cut__1->SetBinContent(172,1);
   h_z2_cut__1->SetBinContent(173,2);
   h_z2_cut__1->SetBinContent(174,2);
   h_z2_cut__1->SetBinContent(175,6);
   h_z2_cut__1->SetBinContent(176,2);
   h_z2_cut__1->SetBinContent(177,4);
   h_z2_cut__1->SetBinContent(178,4);
   h_z2_cut__1->SetBinContent(181,4);
   h_z2_cut__1->SetBinContent(182,1);
   h_z2_cut__1->SetBinContent(183,1);
   h_z2_cut__1->SetBinContent(184,5);
   h_z2_cut__1->SetBinContent(185,4);
   h_z2_cut__1->SetBinContent(186,3);
   h_z2_cut__1->SetBinContent(187,2);
   h_z2_cut__1->SetBinContent(188,5);
   h_z2_cut__1->SetBinContent(189,3);
   h_z2_cut__1->SetBinContent(190,4);
   h_z2_cut__1->SetBinContent(191,4);
   h_z2_cut__1->SetBinContent(192,5);
   h_z2_cut__1->SetBinContent(193,3);
   h_z2_cut__1->SetBinContent(194,7);
   h_z2_cut__1->SetBinContent(195,7);
   h_z2_cut__1->SetBinContent(196,8);
   h_z2_cut__1->SetBinContent(198,4);
   h_z2_cut__1->SetBinContent(199,1);
   h_z2_cut__1->SetBinContent(200,1);
   h_z2_cut__1->SetBinContent(201,4);
   h_z2_cut__1->SetBinContent(202,5);
   h_z2_cut__1->SetBinContent(203,1);
   h_z2_cut__1->SetBinContent(204,3);
   h_z2_cut__1->SetBinContent(205,4);
   h_z2_cut__1->SetBinContent(206,4);
   h_z2_cut__1->SetBinContent(207,2);
   h_z2_cut__1->SetBinContent(208,1);
   h_z2_cut__1->SetBinContent(209,3);
   h_z2_cut__1->SetBinContent(210,3);
   h_z2_cut__1->SetBinContent(211,5);
   h_z2_cut__1->SetBinContent(212,1);
   h_z2_cut__1->SetBinContent(213,1);
   h_z2_cut__1->SetBinContent(214,3);
   h_z2_cut__1->SetBinContent(215,2);
   h_z2_cut__1->SetBinContent(216,1);
   h_z2_cut__1->SetBinContent(217,3);
   h_z2_cut__1->SetBinContent(219,4);
   h_z2_cut__1->SetBinContent(220,2);
   h_z2_cut__1->SetBinContent(222,1);
   h_z2_cut__1->SetBinContent(223,1);
   h_z2_cut__1->SetBinContent(225,2);
   h_z2_cut__1->SetBinContent(226,1);
   h_z2_cut__1->SetBinContent(227,1);
   h_z2_cut__1->SetBinContent(229,1);
   h_z2_cut__1->SetBinContent(230,1);
   h_z2_cut__1->SetBinContent(232,1);
   h_z2_cut__1->SetBinContent(239,1);
   h_z2_cut__1->SetBinContent(243,1);
   h_z2_cut__1->SetBinContent(245,2);
   h_z2_cut__1->SetBinContent(246,1);
   h_z2_cut__1->SetBinContent(249,1);
   h_z2_cut__1->SetBinContent(250,2);
   h_z2_cut__1->SetBinContent(251,1);
   h_z2_cut__1->SetBinContent(252,1);
   h_z2_cut__1->SetBinContent(254,1);
   h_z2_cut__1->SetBinContent(255,1);
   h_z2_cut__1->SetBinContent(256,2);
   h_z2_cut__1->SetBinContent(257,1);
   h_z2_cut__1->SetBinContent(258,1);
   h_z2_cut__1->SetBinContent(260,1);
   h_z2_cut__1->SetBinContent(262,1);
   h_z2_cut__1->SetBinContent(263,2);
   h_z2_cut__1->SetBinContent(264,3);
   h_z2_cut__1->SetBinContent(265,3);
   h_z2_cut__1->SetBinContent(266,2);
   h_z2_cut__1->SetBinContent(267,4);
   h_z2_cut__1->SetBinContent(268,1);
   h_z2_cut__1->SetBinContent(269,5);
   h_z2_cut__1->SetBinContent(270,3);
   h_z2_cut__1->SetBinContent(271,5);
   h_z2_cut__1->SetBinContent(272,6);
   h_z2_cut__1->SetBinContent(273,4);
   h_z2_cut__1->SetBinContent(274,3);
   h_z2_cut__1->SetBinContent(275,4);
   h_z2_cut__1->SetBinContent(276,2);
   h_z2_cut__1->SetBinContent(277,4);
   h_z2_cut__1->SetBinContent(278,8);
   h_z2_cut__1->SetBinContent(279,6);
   h_z2_cut__1->SetBinContent(280,3);
   h_z2_cut__1->SetBinContent(281,5);
   h_z2_cut__1->SetBinContent(282,3);
   h_z2_cut__1->SetBinContent(283,2);
   h_z2_cut__1->SetBinContent(284,4);
   h_z2_cut__1->SetBinContent(285,1);
   h_z2_cut__1->SetBinContent(286,1);
   h_z2_cut__1->SetBinContent(287,1);
   h_z2_cut__1->SetBinContent(288,5);
   h_z2_cut__1->SetBinContent(289,2);
   h_z2_cut__1->SetBinContent(290,5);
   h_z2_cut__1->SetBinContent(291,6);
   h_z2_cut__1->SetBinContent(292,6);
   h_z2_cut__1->SetBinContent(293,1);
   h_z2_cut__1->SetBinContent(294,2);
   h_z2_cut__1->SetBinContent(295,1);
   h_z2_cut__1->SetBinContent(296,1);
   h_z2_cut__1->SetBinContent(298,2);
   h_z2_cut__1->SetBinContent(301,2);
   h_z2_cut__1->SetBinContent(302,1);
   h_z2_cut__1->SetBinContent(303,1);
   h_z2_cut__1->SetBinContent(304,1);
   h_z2_cut__1->SetBinContent(306,1);
   h_z2_cut__1->SetBinContent(308,4);
   h_z2_cut__1->SetBinContent(309,4);
   h_z2_cut__1->SetBinContent(310,1);
   h_z2_cut__1->SetBinContent(312,4);
   h_z2_cut__1->SetBinContent(313,1);
   h_z2_cut__1->SetBinContent(316,1);
   h_z2_cut__1->SetBinContent(318,4);
   h_z2_cut__1->SetBinContent(319,2);
   h_z2_cut__1->SetBinContent(320,3);
   h_z2_cut__1->SetBinContent(321,2);
   h_z2_cut__1->SetBinContent(322,4);
   h_z2_cut__1->SetBinContent(323,3);
   h_z2_cut__1->SetBinContent(324,5);
   h_z2_cut__1->SetBinContent(325,5);
   h_z2_cut__1->SetBinContent(326,4);
   h_z2_cut__1->SetBinContent(327,3);
   h_z2_cut__1->SetBinContent(328,8);
   h_z2_cut__1->SetBinContent(329,14);
   h_z2_cut__1->SetBinContent(330,12);
   h_z2_cut__1->SetBinContent(331,16);
   h_z2_cut__1->SetBinContent(332,13);
   h_z2_cut__1->SetBinContent(333,39);
   h_z2_cut__1->SetBinContent(334,25);
   h_z2_cut__1->SetBinContent(335,21);
   h_z2_cut__1->SetBinContent(336,49);
   h_z2_cut__1->SetBinContent(337,49);
   h_z2_cut__1->SetBinContent(338,41);
   h_z2_cut__1->SetBinContent(339,66);
   h_z2_cut__1->SetBinContent(340,64);
   h_z2_cut__1->SetBinContent(341,52);
   h_z2_cut__1->SetBinContent(342,53);
   h_z2_cut__1->SetBinContent(343,69);
   h_z2_cut__1->SetBinContent(344,81);
   h_z2_cut__1->SetBinContent(345,59);
   h_z2_cut__1->SetBinContent(346,78);
   h_z2_cut__1->SetBinContent(347,80);
   h_z2_cut__1->SetBinContent(348,91);
   h_z2_cut__1->SetBinContent(349,79);
   h_z2_cut__1->SetBinContent(350,83);
   h_z2_cut__1->SetBinContent(351,115);
   h_z2_cut__1->SetBinContent(352,121);
   h_z2_cut__1->SetBinContent(353,109);
   h_z2_cut__1->SetBinContent(354,120);
   h_z2_cut__1->SetBinContent(355,126);
   h_z2_cut__1->SetBinContent(356,167);
   h_z2_cut__1->SetBinContent(357,162);
   h_z2_cut__1->SetBinContent(358,154);
   h_z2_cut__1->SetBinContent(359,200);
   h_z2_cut__1->SetBinContent(360,155);
   h_z2_cut__1->SetBinContent(361,223);
   h_z2_cut__1->SetBinContent(362,226);
   h_z2_cut__1->SetBinContent(363,266);
   h_z2_cut__1->SetBinContent(364,269);
   h_z2_cut__1->SetBinContent(365,303);
   h_z2_cut__1->SetBinContent(366,314);
   h_z2_cut__1->SetBinContent(367,358);
   h_z2_cut__1->SetBinContent(368,389);
   h_z2_cut__1->SetBinContent(369,376);
   h_z2_cut__1->SetBinContent(370,380);
   h_z2_cut__1->SetBinContent(371,439);
   h_z2_cut__1->SetBinContent(372,378);
   h_z2_cut__1->SetBinContent(373,454);
   h_z2_cut__1->SetBinContent(374,393);
   h_z2_cut__1->SetBinContent(375,367);
   h_z2_cut__1->SetBinContent(376,409);
   h_z2_cut__1->SetBinContent(377,372);
   h_z2_cut__1->SetBinContent(378,355);
   h_z2_cut__1->SetBinContent(379,348);
   h_z2_cut__1->SetBinContent(380,287);
   h_z2_cut__1->SetBinContent(381,316);
   h_z2_cut__1->SetBinContent(382,251);
   h_z2_cut__1->SetBinContent(383,217);
   h_z2_cut__1->SetBinContent(384,231);
   h_z2_cut__1->SetBinContent(385,173);
   h_z2_cut__1->SetBinContent(386,182);
   h_z2_cut__1->SetBinContent(387,140);
   h_z2_cut__1->SetBinContent(388,145);
   h_z2_cut__1->SetBinContent(389,109);
   h_z2_cut__1->SetBinContent(390,115);
   h_z2_cut__1->SetBinContent(391,107);
   h_z2_cut__1->SetBinContent(392,66);
   h_z2_cut__1->SetBinContent(393,60);
   h_z2_cut__1->SetBinContent(394,61);
   h_z2_cut__1->SetBinContent(395,60);
   h_z2_cut__1->SetBinContent(396,50);
   h_z2_cut__1->SetBinContent(397,49);
   h_z2_cut__1->SetBinContent(398,53);
   h_z2_cut__1->SetBinContent(399,28);
   h_z2_cut__1->SetBinContent(400,41);
   h_z2_cut__1->SetBinContent(401,53);
   h_z2_cut__1->SetBinContent(402,31);
   h_z2_cut__1->SetBinContent(403,38);
   h_z2_cut__1->SetBinContent(404,30);
   h_z2_cut__1->SetBinContent(405,24);
   h_z2_cut__1->SetBinContent(406,32);
   h_z2_cut__1->SetBinContent(407,33);
   h_z2_cut__1->SetBinContent(408,25);
   h_z2_cut__1->SetBinContent(409,25);
   h_z2_cut__1->SetBinContent(410,30);
   h_z2_cut__1->SetBinContent(411,22);
   h_z2_cut__1->SetBinContent(412,13);
   h_z2_cut__1->SetBinContent(413,15);
   h_z2_cut__1->SetBinContent(414,10);
   h_z2_cut__1->SetBinContent(415,14);
   h_z2_cut__1->SetBinContent(416,13);
   h_z2_cut__1->SetBinContent(417,8);
   h_z2_cut__1->SetBinContent(418,5);
   h_z2_cut__1->SetBinContent(419,8);
   h_z2_cut__1->SetBinContent(420,9);
   h_z2_cut__1->SetBinContent(421,6);
   h_z2_cut__1->SetBinContent(422,2);
   h_z2_cut__1->SetBinContent(423,7);
   h_z2_cut__1->SetBinContent(424,2);
   h_z2_cut__1->SetBinContent(425,6);
   h_z2_cut__1->SetBinContent(426,4);
   h_z2_cut__1->SetBinContent(427,4);
   h_z2_cut__1->SetBinContent(428,1);
   h_z2_cut__1->SetBinContent(429,2);
   h_z2_cut__1->SetBinContent(431,6);
   h_z2_cut__1->SetBinContent(433,1);
   h_z2_cut__1->SetBinContent(438,1);
   h_z2_cut__1->SetBinContent(439,1);
   h_z2_cut__1->SetBinContent(446,1);
   h_z2_cut__1->SetBinContent(462,1);
   h_z2_cut__1->SetBinContent(501,2);

   TF1 * f = new TF1("f","2.*gaus(x-[3],[0],0,[1])*ROOT::Math::normal_cdf([2]*(x-[3]),1,0)",7,10);
   f->SetParameters(400,0.5,-10,8.5);
   f->Draw();
   h_z2_cut__1->Fit(f, "", "",7,10);
   h_z2_cut__1->Draw();


   /* 
    // Fit with 3 Gaussians.
   double par[9];
   TF1 *g1 = new TF1("g1", "gaus", 7.5, 8.2);
   TF1 *g2 = new TF1("g2", "gaus", 8.2, 8.7);
   TF1 *g3 = new TF1("g3", "gaus", 8.7, 9);
   TF1 *total = new TF1("total", "gaus(0)+gaus(3)+gaus(6)", 7, 10);
   total->SetLineColor(2);
   h_z2_cut__1->Fit(g1, "R");
   h_z2_cut__1->Fit(g2, "R+");
   h_z2_cut__1->Fit(g3, "R+");
   g1->GetParameters(&par[0]);
   g2->GetParameters(&par[3]);
   g3->GetParameters(&par[6]);
   total->SetParameters(par);
   h_z2_cut__1->Fit(total, "R+");*/

}


