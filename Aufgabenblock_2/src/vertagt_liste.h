#pragma once

#include "vertagt_aktion.h"
#include <list>

namespace vertagt
{
	template <class T>
	class VListe
	{
	private:
		std::list<T> p_objekte;
		std::list<std::unique_ptr<VAktion<T>>> p_aktionen;

	public:
		// Typdefinitionen
		using iterator = typename std::list<T>::iterator;
		using const_iterator = typename std::list<T>::const_iterator;

		// Konstruktoren
		VListe() = default; // Benötigt man einen Standardkonstruktor? -> Nö, nicht wirklich aber ist nett
		// Destruktor
		~VListe()
		{
			vAktualisieren();
			p_objekte.clear();
		}

		void clear()//void clear(): aktualisiert die Liste und l¨oscht dann alle Elemente in p objekte
		{
			vAktualisieren();
			p_objekte.clear();
		}

		// Lesefunktionen
		const_iterator begin() const
		{
			return p_objekte.begin();
		}
		const_iterator end() const
		{
			return p_objekte.end();
		}
		iterator begin()//• iterator begin(): gibt einen Iterator zur¨uck, der auf das erste Element zeigt
		{
			return p_objekte.begin();
		}
		iterator end()///iterator end(): gibt einen Iterator zur¨uck, der hinter das letzte Element zeigt
		{
			return p_objekte.end();
		}
		bool empty() const//bool empty(): gibt zur¨uck, ob das Objekt keine Elemente enth¨alt
		{
			return p_objekte.empty();
		}

		// Schreibfunktionen
		void push_back(T obj)//• void push back(T obj): f¨ugt obj am Ende ein
		{
			// Aktionselement für PushBack auf Liste erzeugen
			p_aktionen.push_back(std::make_unique<VPushBack<T>>(p_objekte, std::move(obj)));
		}

		void push_front(T obj)//void push front(T obj): f¨ugt obj vor dem ersten Element ein
		{
			// Aktionselement für PushFront auf Liste erzeugen
			p_aktionen.push_back(std::make_unique<VPushFront<T>>(p_objekte, std::move(obj)));
		}

		void erase(iterator it)//void erase(iterator it): l¨oscht das Element an Position it
		{
			// Aktionselement für PushBack auf Liste erzeugen (hier Iterator statt Objekt !)
			p_aktionen.push_back(std::make_unique<VErase<T>>(p_objekte, it));
		}

		// Änderungen auf Objektliste übertragen
		void vAktualisieren()//• void vAktualisieren(): aktualisiert p objekte
		{
			// Änderungen auf Objektliste übertragen
			for (auto& pAktion : p_aktionen)
			{
				// Aktion ausführen
				pAktion->vAusfuehren();
			}
			// Aktionsliste löschen
			p_aktionen.clear();
		}
	};
} // namespace vertagt
